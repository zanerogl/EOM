#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Init();

    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//临时函数
void MainWindow::temp_function()
{
    qDebug()<<"temp_function";
}

//初始化
bool MainWindow::Init()
{
    ui->menuCamera->setIcon(QIcon(":/res/camera.png"));
    ui->actionLocal_Camera->setIcon(QIcon(":/res/local_camera.png"));
    ui->actionIP_Camera->setIcon(QIcon(":/res/ip_camera.png"));
    ui->actionAbout->setIcon(QIcon(":/res/about.png"));
//    ui->actionIP_Camera_Setting->setIcon(QIcon(":/res/ip_setting.png"));
    ui->progressBar->setTextVisible(false); //隐藏进度条文本

    this->setWindowTitle(" ");
    this->setWindowIcon(QIcon(":/res/Zanerogl.png"));

    //按下 local camera 打开本地摄像头
    connect(ui->actionLocal_Camera, &QAction::triggered, this, &MainWindow::local_camera_open);

    //点击模板图片
    connect(ui->template_image, SIGNAL(is_clicked()), this, SLOT(templates_show()));

    return true;
}

//关闭程序
void MainWindow::on_quit_button_clicked()
{
    //先释放摄像头
    if(capture.isOpened()){
        capture.release();
        delete camera_timer;
        camera_timer = nullptr;
    }
    this->close();
}

//清除log
void MainWindow::on_clear_button_clicked()
{
    ui->log->clear();
}

//打开本地摄像头（先开usb摄像头）,按第二次释放摄像头
void MainWindow::local_camera_open()
{
    if(capture.isOpened()){
        capture.release();
        ui->screen->setPixmap(QPixmap());
        delete camera_timer;
        camera_timer = nullptr;
        ui->log->append("Camera is off.");
    }
    else{
        capture.open(1);
        if(!capture.isOpened()){
            qDebug() << "Camera 1 not detected";
            capture.open(0);
        }
        if(!capture.isOpened()){
            qDebug() << "Camera 0 not detected";
            ui->log->append("Can't open the camera");
        }
        else{
            ui->log->append("Camera is on.");
            camera_timer = new QTimer(this);
            connect(camera_timer, &QTimer::timeout, this, [=](){
                camera_timer->stop();
                //捕获图像帧
                capture>>frame;
                //将视频显示到screen上
                QImage image = QImage((const uchar*)frame.data, frame.cols, frame.rows, QImage::Format_RGB888).rgbSwapped();
                ui->screen->setPixmap(QPixmap::fromImage(image));
                camera_timer->start(25);
            });
            qDebug() << "Frame width: " << capture.get(cv::CAP_PROP_FRAME_WIDTH) << endl;
            qDebug() << "     Height: " << capture.get(cv::CAP_PROP_FRAME_HEIGHT) << endl;
            qDebug() << "Capturing FPS: " << capture.get(cv::CAP_PROP_FPS) << endl;

            camera_timer->start(25);
        }
    }

}

//拍照
cv::Mat MainWindow::camera_capture(cv::Mat frame)
{
    capture>>frame;     //获取图像帧
    return frame;
}

//获取模板照片
void MainWindow::on_capture_clicked()
{
    if(!capture.isOpened()){
        ui->log->append("Please open the camera first.");
    }
    else
    {
        if(ui->num_of_tem->value() > templates_num){
            templates_num++;     //计数器++
            ui->progressBar->setValue((templates_num/ui->num_of_tem->value())*100.0);
            qDebug()<<(templates_num/ui->num_of_tem->value())*100.0;

            img_templates_cv.push_back(camera_capture(frame_temp));         //将拍到的图片存到vector中

            // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
            QImage image = QImage((const uchar*)camera_capture(frame_temp).data, camera_capture(frame_temp).cols, camera_capture(frame_temp).rows, QImage::Format_RGB888).rgbSwapped();

            //将拍到的照片等比例缩放到模板template_image上
            ui->template_image->setPixmap(QPixmap::fromImage(image).scaled(ui->template_image->width(), ui->template_image->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        else
        {
            ui->log->append("Exceeded the set limit");
        }
    }
}

//展示模板集
void MainWindow::templates_show()
{
    if(img_templates_cv.size() != 0){
        for (unsigned long long i = 0; i < img_templates_cv.size(); i++) {
            // 将Mat格式转换为QImage格式，存入容器，QImage::Format_RGB888不同的摄像头用不同的格式
            QImage img = QImage((const uchar*)img_templates_cv.at(i).data, img_templates_cv.at(i).cols, img_templates_cv.at(i).rows, QImage::Format_RGB888).rgbSwapped();
            img_templates_qt.push_back(img);
        }
//        itw = new img_template_widget(img_templates_qt);
        itw = new img_template_widget;
        itw->img_saver(img_templates_cv);
//        qDebug()<<"The number of templates: "<<itw->img_templates_size;
        itw->show();
        itw->img_dispaly(0);
    }
}

//清除模板照片
void MainWindow::on_clear_templates_clicked()
{
    templates_num = 0;
    ui->num_of_tem->setValue(templates_num);
    img_templates_cv.clear();
    vector<cv::Mat>().swap(img_templates_cv);
    ui->log->append("Template has been cleared.");
    ui->template_image->clear();    //清空模板显示label
    ui->progressBar->reset();       //重置进度条
}

//服务器监听端口
bool MainWindow::server_open_port(int port)
{
    tcpServer = new QTcpServer;
//    if(tcpServer->listen(QHostAddress::Any, port))
    if(tcpServer->listen(QHostAddress::AnyIPv4, port))  //Any是同时监听ipv4和ipv6的端口，ipv6的端口还没有被占用，所以返回值为ture
    {
        qDebug() << "Server status for listening ok: " << tcpServer->isListening();
        qDebug() << "Server listen on " << tcpServer->serverAddress() << ":" << tcpServer->serverPort();

        ui->log->clear();
        qDebug()<<"Tcp server started";
        ui->log->append("Tcp server started");
        server_is_open = true;
        //等待客户端连接
        connect(tcpServer, &QTcpServer::newConnection, [=](){
            //调用 nextPendingConnection()去接受一个等待的连接，返回一个指向QTcpSocket如果出现了错误，将会返回一个错误类型，可以调用errorString(),以此来返回一个可读的字符串
            tcpSocket = tcpServer->nextPendingConnection();

            QString ip = tcpSocket->peerAddress().toString();
            qint16 port = tcpSocket->peerPort();

//            ui->log->clear();
//            QString temp = QString("[%1：%2]:successfully connected").arg(ip).arg(port);
            QString temp = QString("[%1]:successfully connected").arg(ip);
            qDebug()<<temp;

            ui->log->append(temp);

        //        emit this->newConnection();
//            QString ViewData;
//            while(ViewData.size()>1024) ViewData.remove(0, 30);// 清掉过多的发送接收数据缓存
//            ViewData.append("<font color=blue>[");
//            ViewData.append(QTime::currentTime().toString("hh:mm:ss.zzz"));
//            ViewData.append("]   ");

            //读取服务器数据
            connect(tcpSocket, &QTcpSocket::readyRead, [=](){
    //            ui->log->clear();
                QByteArray array = tcpSocket->readAll();

                std::string test = array.toStdString();
                std::cout<<test<<endl;

//                cv::Mat temp = imread(":/res/test.jpg");

                //机器人发送开始信号，拍照获取颜色、角度、数字，将计算结果按"xxx,yyy,zzz"格式返回
                if(test == "startup"){
                    result.clear();
                    if(!capture.isOpened())
                    {
                        ui->log->append("Error: Camera is not turned on.");
                        qDebug()<<"ERROR camera is disable.";
                    }
                    else if (img_templates_cv.empty() ) {
                        ui->log->append("No templates set.");
                    }
                    else if (templates_num < ui->num_of_tem->value()) {
                        ui->log->append("Please record the template set first.");
                    }
                    else
                    {
                        cv::Mat img = camera_capture(frame);             //拍照获取图像

                        // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
                        QImage image = QImage((const uchar*)camera_capture(frame).data,camera_capture(frame).cols,camera_capture(frame).rows,QImage::Format_RGB888).rgbSwapped();
                        //将拍到的照片等比例缩放到模板Label上
                        ui->captured_image->setPixmap(QPixmap::fromImage(image).scaled(ui->captured_image->width(), ui->captured_image->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

                        //颜色识别
                        col_detector = new color_detector(img); //将获取的图像做颜色检测
                        result += col_detector->color_result() + ",";

                        qDebug()<<result;

//                      //角度识别+数字识别
//                        img_template.push_back(imread("./photo2-1.jpg"));   //读取图片
//                        img_template.push_back(imread("./photo3.jpg"));     //读取图片
//                        vector<string> files;
//                        glob(std::move("./"),files);
//                        for(auto &file : files){
//                            img_template.push_back(imread(file));
//                        }
                        //判断图片容器是否为空
                        if(img_templates_cv.empty()){
                            qDebug()<<"empty!";
                        }
                        //不为空则imshow整个容器里的图片
                        else{
                            qDebug()<<"no empty!";
//                            for(auto& img : img_template){
//                                static int id = 0;
//                                imshow("aa"+to_string(id++),img);
//                                qDebug()<<"*************************";
//                                qDebug()<<&img;
//                            }
                            //角度识别+数字识别类
                            a = new Angle_detector(img, img_templates_cv);
                            result += QString::fromLocal8Bit(a->m_strAngle.c_str());

                            result += ",";
                            result += QString::fromLocal8Bit(a->m_strNumber.c_str());

//                            cv::Mat imgmo = imread("D:\\Project\\C++\\Qt\\2022\\5\\Interface\\5\\resources\\mo1.png");
//                            agl_detector = new angle_detector(imgmo,img);     //有bug，模板路径未添加
//                            result += agl_detector->angle_result() + ",";

                            qDebug()<<result;

                            //数字识别
                            qDebug()<<result;
                            ui->log->append("Server: "+result);
                            server_send(result);    //返回结果
                            delete a, delete col_detector;
                        }
                    }
                }
                qDebug()<<"size:"<<array.size();
                int i;
                for (i = 0 ;i< array.size();i++) {
                    if (array[i]!='\0') break;
                }
                array.remove(0,i);
                ui->log->append("Client: "+array);

        //            emit this->newMessage();
//                QString ViewData;
//                while(ViewData.size()>1024) ViewData.remove(0, 30);// 清掉过多的发送接收数据缓存
//                ViewData.append("<font color=blue>[");
//                ViewData.append(QTime::currentTime().toString("hh:mm:ss.zzz"));
//                ViewData.append("]   ");
            });
        });

    }
    else
    {
        ui->log->setText("Port is occupied\nPlease use another port");
        qDebug() << "Server status for listening fail" << tcpServer->isListening();
        delete tcpServer;
        tcpServer = nullptr;
        server_is_open = false;
    }
    return server_is_open;
}

//服务器发送数据
void MainWindow::server_send(const QString &data)
{
//    ui->log->clear();
    if(data == "")
    {
        qDebug()<<"Can not send empty text";
        ui->log->append("Can not send empty text");
        return;
    }
    if(tcpSocket== nullptr)
    {
        qDebug()<<"cannot find client";
        ui->log->append("cannot find client");
        return;
    }
    //给对方发送数据，使用套接字是tcpSocket
    tcpSocket->write(data.toUtf8().data());
}

//服务器启动/关闭按钮
void MainWindow::on_server_startup_clicked()
{
    if(ui->server_startup->text() == "Server startup")
    {
        qDebug()<<"port: "<<ui->port->text().toUInt();
        server_open_port(ui->port->text().toUInt()); //服务器开启端口
        if(server_is_open){
            ui->server_startup->setText("Shut down server");
        }
    }
    else if(ui->server_startup->text() == "Shut down server" && server_is_open)
    {
        tcpServer->close();                             //服务器停止监听端口
        tcpServer->deleteLater();                       //不立即销毁对象，向主消息循环发送了一个event，下一次主消息循环收到这个event之后才会销毁对象
        ui->log->setText("Server is down");
        ui->server_startup->setText("Server startup");
    }
}

//重写关闭事件
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (capture.isOpened())
    {
        capture.release();
    }
}

//测试按钮
void MainWindow::on_test_clicked()
{
    if(temp0 < temp1){
        temp0++;
        ui->progressBar->setValue(temp0/temp1 * 100);
    }
}
