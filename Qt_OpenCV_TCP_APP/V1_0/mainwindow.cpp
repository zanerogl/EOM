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
        if(ui->num_of_tem->value() > template_num){
            template_num++;     //计数器++
            ui->progressBar->setValue((template_num/ui->num_of_tem->value())*100.0);
            qDebug()<<(template_num/ui->num_of_tem->value())*100.0;

            img_template.push_back(camera_capture(frame_temp));         //将拍到的图片存到vector中

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
    if(img_template.size() != 0){
        itw = new img_template_widget;
        itw->img_saver(img_template);
        qDebug()<<"The number of templates: "<<itw->img_templates_size;
        itw->show();
    }
}

//清除模板照片
void MainWindow::on_clear_templates_clicked()
{
    template_num = 0;
    ui->num_of_tem->setValue(template_num);
    img_template.clear();
    vector<cv::Mat>().swap(img_template);
    ui->log->append("Template has been cleared.");
    ui->template_image->clear();    //清空模板显示label
    ui->progressBar->reset();       //重置进度条
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
