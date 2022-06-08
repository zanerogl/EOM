#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

/*************************************************** BUG 日志 ***************************************************/
/*
    时间             内容                                      作者          状态       原因
    20220529        ip摄像头按两次cancel就会出现程序异常          Zanerogl      已解决     未知
    20220530        两个摄像头开的次数越多越卡                    Zanerogl      已解决     未释放定时器
    20220603        capture捕获模板集后只能显示捕获的最后一张      Zanerogl      已解决     未知
*/
/*************************************************** ******* ***************************************************/



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MennBarInit();

    this->setWindowTitle(" ");
    this->setWindowIcon(QIcon(":/res/Zanerogl.png"));
    this->camera_timer = new QTimer(this);
    this->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//菜单初始化
void MainWindow::MennBarInit()
{
    ui->actionQuit->setIcon(QIcon(":/res/quit.png"));
    ui->menuCamera->setIcon(QIcon(":/res/camera.png"));
    ui->actionLocal_Camera->setIcon(QIcon(":/res/local_camera.png"));
    ui->actionIP_Camera->setIcon(QIcon(":/res/ip_camera.png"));
    ui->actionAbout->setIcon(QIcon(":/res/about.png"));
//    ui->screen->setPixmap(QPixmap(":/res/screen.png"));
//    ui->original_image->setPixmap(QPixmap(":/res/original_image.png"));
//    ui->captured_image->setPixmap(QPixmap(":/res/captured_image.png"));

    //按下 local camera 打开本地摄像头
    connect(ui->actionLocal_Camera, &QAction::triggered, this, &MainWindow::local_camera_open);

    //按下 ip camera 按钮，打开ip设置窗口
    connect(ui->actionIP_Camera, &QAction::triggered, this, [=](){
        ip_camera_setting_widget = new ip_camera_setting;
        ip_camera_setting_widget->show();
        static auto ConnectClickedSlot = connect(this->ip_camera_setting_widget, SIGNAL(send(std::string, std::string)), this, SLOT(ip_camera_open(std::string, std::string)));
    });

    //按下 about 按钮
    connect(ui->actionAbout, &QAction::triggered, this, [=](){
        QDesktopServices::openUrl(QUrl(QString("https://zanerogl.github.io/")));
    });

//    //按钮 logout 按钮
//    connect(ui->actionLogout, &QAction::triggered, this, [=](){
//        this->destroy();
//    });

}

//关闭程序
void MainWindow::on_quit_button_clicked()
{
    //先释放摄像头
    if(capture.isOpened()){
        capture.release();
//        ui->screen->setPixmap(QPixmap());
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
//        ui->screen->setPixmap(QPixmap());
        delete camera_timer;
        camera_timer = nullptr;
    }
    else{
        capture.open(1);
        if(!capture.isOpened()){
    //        qDebug() << "ERROR: Can't initialize camera capture" << endl;
            capture.open(0);
        }
        if(!capture.isOpened()){
            qDebug() << "ERROR: Can't initialize camera capture" << endl;
            ui->log->append("Can't open the camera");
        }
        else{
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

            qDebug() << "Frame width: " << capture.get(CAP_PROP_FRAME_WIDTH) << endl;
            qDebug() << "     height: " << capture.get(CAP_PROP_FRAME_HEIGHT) << endl;
            qDebug() << "Capturing FPS: " << capture.get(CAP_PROP_FPS) << endl;

            camera_timer->start(25);
        }
    }

}

//打开ip摄像头
void MainWindow::ip_camera_open(std::string address, std::string port)
{
    if(capture.isOpened()){
        capture.release();
//        ui->screen->setPixmap(QPixmap());
        delete camera_timer;
        camera_timer = nullptr;
    }
//    if(capture.isOpened()){
//        capture.release();
//    }
    capture.open("http://" + address + ":" + port + "/video");
//    capture.open("http://admin:admin@" + address + ":" + port);
    if(!capture.isOpened())
    {
        qDebug() << "ERROR: Can't initialize camera capture" << endl;
        ui->log->append("Can't open the camera");
        std::cout << address << port<<endl;
    }
    else
    {
        QTimer *camera_timer;
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

        qDebug() << "Frame width: " << capture.get(CAP_PROP_FRAME_WIDTH) << endl;
        qDebug() << "     height: " << capture.get(CAP_PROP_FRAME_HEIGHT) << endl;
        qDebug() << "Capturing FPS: " << capture.get(CAP_PROP_FPS) << endl;

        camera_timer->start(25);
    }
}

//拍照
cv::Mat MainWindow::camera_capture(cv::Mat frame)
{
    //获取图像帧
    capture>>frame;

    // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
    QImage image = QImage((const uchar*)frame.data,frame.cols,frame.rows,QImage::Format_RGB888).rgbSwapped();

    //将拍到的照片等比例缩放到模板Label上
    ui->captured_image->setPixmap(QPixmap::fromImage(image).scaled(ui->captured_image->width(), ui->captured_image->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    return frame;
}

//服务器监听端口
void MainWindow::server_open_port(int port)
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

        //等待客户端连接
        connect(tcpServer, &QTcpServer::newConnection, [=](){
            //调用 nextPendingConnection()去接受一个等待的连接，返回一个指向QTcpSocket如果出现了错误，将会返回一个错误类型，可以调用errorString(),以此来返回一个可读的字符串
            tcpSocket = tcpServer->nextPendingConnection();

            QString ip = tcpSocket->peerAddress().toString();
            qint16 port = tcpSocket->peerPort();

    //        ui->log->clear();
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
                        ui->log->append("Error: Camera is not turned on");
                        qDebug()<<"ERROR camera is disable.";
                    }
                    else
                    {
                        Mat img = camera_capture(frame);             //拍照获取图像

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
                        if(img_template.empty()){
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
                            a = new Angle_detector(img, img_template);
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
    }
}

//服务器接受连接（有bug，已废弃）
void MainWindow::server_accept_connection()
{
    //调用 nextPendingConnection()去接受一个等待的连接，返回一个指向QTcpSocket如果出现了错误，将会返回一个错误类型，可以调用errorString(),以此来返回一个可读的字符串
    tcpSocket = tcpServer->nextPendingConnection();

    QString ip = tcpSocket->peerAddress().toString();
    qint16 port = tcpSocket->peerPort();

    ui->log->clear();
    QString temp = QString("[%1：%2]:successfully connected").arg(ip).arg(port);
    qDebug()<<temp;

    ui->log->append(temp);

//        emit this->newConnection();
//    QString ViewData;
//    while(ViewData.size()>1024) ViewData.remove(0, 30);// 清掉过多的发送接收数据缓存
//    ViewData.append("<font color=blue> [");
//    ViewData.append(QTime::currentTime().toString("hh:mm:ss.zzz"));
//    ViewData.append("]   ");

    connect(tcpSocket, &QTcpSocket::readyRead, [=](){
//        ui->log->clear();
        QByteArray array = tcpSocket->readAll();

        QString temp = array;
        temp.prepend(array);

        qDebug()<<temp<<endl;
        //使用settext可以将以前的进行覆盖，使用append会在后面添加
        qDebug()<<"size:"<<array.size();
        qDebug()<<array<<endl;
        int i;
        for (i = 0 ;i< array.size();i++) {
            if (array[i]!='\0') break;
        }
        array.remove(0,i);
        ui->log->append(array);

//            emit this->newMessage();
//        QString ViewData;
//        while(ViewData.size()>1024) ViewData.remove(0, 30);// 清掉过多的发送接收数据缓存
//        ViewData.append("<font color=blue>[");
//        ViewData.append(QTime::currentTime().toString("hh:mm:ss.zzz"));
//        ViewData.append("]   ");
    });
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
void MainWindow::on_Server_startup_clicked()
{
    if(ui->Server_startup->text() == "Server startup")
    {
        qDebug()<<"port: "<<ui->port->text().toUInt();
        server_open_port(ui->port->text().toUInt()); //服务器开启端口
        ui->Server_startup->setText("Shut down server");
    }
    else if(ui->Server_startup->text() == "Shut down server")
    {
        tcpServer->close();                             //服务器停止监听端口
        tcpServer->deleteLater();                       //不立即销毁对象，向主消息循环发送了一个event，下一次主消息循环收到这个event之后才会销毁对象
        ui->log->setText("Server is down");
        ui->Server_startup->setText("Server startup");
    }
}

//测试按钮
void MainWindow::on_test_clicked()
{
    //测试拍到的照片
//    std::cout<<temp(camera_capture());
//    QTimer *temp_timer = new QTimer(this);
//    temp_timer->start(25);

//    connect(temp_timer, &QTimer::timeout, this, [=](){
//        temp_timer->stop();
//        delete temp_timer;
////        int i = 6;
//        imshow("asad",camera_capture(frame));
////        cv::imwrite("D:/capture.jpg", camera_capture());
////        i++;
//    });
    //测试发送
//    server_send("ad");

    //测试模板图片集
//    if(img_template.empty()){
//        qDebug()<<"Empty";
//    }
//    else{
//        qDebug()<<"Size"<<img_template.size();
//    }

//    for(auto& i : img_template ){
//        static int id = 0;
//        imshow("aa"+to_string(id++),i);
//        qDebug()<<"*************************";
//        qDebug()<<&i;
//    }
////    imshow("xx",frame);


//    //测试发送
    server_send("0,150,2\0");



}

//临时函数
std::string MainWindow::temp( cv::Mat frame )
{
    std::string mc;
    if (frame.empty()){
        mc = "Empty";
    }else{
        mc = "Not empty!";
    }
    return mc;
}

//颜色识别（封装成类，已废弃）
std::string MainWindow::detect_color(cv::Mat imgOriginal)
{
    //只识别红色
    //resize(imgOriginal, imgOriginal, Size(500, 500)); // 重新设置图片大小
        Mat imgBGR;
        Mat imgThresholded; // 阈值图像
        imgBGR = imgOriginal.clone();

//        cv::Scalar lower_red_1 = cv::Scalar(0, 50, 50);
//        cv::Scalar upper_red_1 = cv::Scalar(10, 255, 255);

//        cv::Scalar lower_red_2 = cv::Scalar(156, 50, 50);
//        cv::Scalar upper_red_2 = cv::Scalar(180, 255, 255);

//        cv::Scalar lower_red_3 = lower_red_1 + lower_red_2;
//        cv::Scalar upper_red_3 = upper_red_1 + upper_red_2;

        inRange(imgBGR, Scalar(0, 0, 128), Scalar(127, 127, 255),
                imgThresholded); //红色阈值

//        inRange(imgBGR, lower_red_3, upper_red_3,
//                imgThresholded); //红色阈值

        Mat element = getStructuringElement(MORPH_RECT, Size(5, 5)); // 设置结构元素
        morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element); // 开运算
        morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element); // 闭运算

    //    imshow("Thresholded Image",imgThresholded); //显示阈值图像
    //    // cv::imwrite("res.jpg", imgThresholded);//保存所得到图像
    //    waitKey();

        int rowNumber = 0;
        int colNumber = 0;
        int WhiteNum = 0;
        rowNumber = imgThresholded.rows;
        colNumber = imgThresholded.cols;
        for (int i = 0; i < rowNumber; i++) {
            for (int j = 0; j < colNumber; j++) {
                if (imgThresholded.ptr<uchar>(i)[j] > 0) {
                    WhiteNum++;
                }
            }
        }
        if(WhiteNum > 50)
        {  // 找到白色
            cout << "red" << endl;//白色像素值大于20，则输出red
            return "001";
        }
        else{
            cout << "no" << endl;
            return "002";  // 纯黑
        }
}

//获取模板照片
void MainWindow::on_capture_clicked()
{
    if(!capture.isOpened()){
        ui->log->append("Please open the camera first.");
    }
    else
    {
        if(ui->num_of_tem->value() > template_num){
            //拍照，获取模板
            capture>>frame_temp;
            qDebug()<<template_num;
            // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
            QImage image = QImage((const uchar*)frame_temp.data,frame_temp.cols,frame_temp.rows,QImage::Format_RGB888).rgbSwapped();
            //将拍到的照片等比例缩放到模板Label上
            ui->original_image->setPixmap(QPixmap::fromImage(image).scaled(ui->original_image->width(), ui->original_image->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            img_template.emplace_back(std::move(frame_temp));     //将拍到的图片存到vector中
            template_num++;
//            return;
        }
        else
        {
            ui->log->append("Exceeded the set limit");
//            //拍照，获取模板
//            capture>>frame_temp;
//            qDebug()<<num;
//            // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
//            QImage image = QImage((const uchar*)frame_temp.data,frame_temp.cols,frame_temp.rows,QImage::Format_RGB888).rgbSwapped();
//            //将拍到的照片等比例缩放到模板Label上
//            ui->original_image->setPixmap(QPixmap::fromImage(image).scaled(ui->original_image->width(), ui->original_image->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
//            img_template.emplace_back(std::move(frame_temp));     //将拍到的图片存到vector中
//            num--;
        }
    }
}

//清除模板照片
void MainWindow::on_clear_templates_clicked()
{
    template_num = 0;
    ui->num_of_tem->setValue(template_num);
    img_template.clear();
    vector<Mat>().swap(img_template);
    ui->log->append("Template has been cleared.");
//    img_template.swap(temp);
}

//重写关闭事件
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (capture.isOpened())
    {
        capture.release();
    }
}
