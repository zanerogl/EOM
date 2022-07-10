#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QString>
#include "ip_camera_setting.h"
#include <iostream>
#include <vector>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDesktopServices>
#include <QUrl>
//#include "color_detector.h"
//#include "angle_detector.h"
#include <QCloseEvent>
#include <QVector>
//#include "contourwithdata.h"
//#include "mylabel.h"
#include "img_template_widget.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool Init();

private slots:
    void on_quit_button_clicked();

    void on_clear_button_clicked();

    void local_camera_open();   //打开本地摄像头

//    void ip_camera_open(std::string address, std::string port);  //打开ip摄像头

    cv::Mat camera_capture(cv::Mat frame); //拍照

//    void server_open_port(int port);    //服务器监听端口

//    void server_accept_connection();    //服务器接受连接

//    void server_send(const QString &data);  //服务器发送数据

    void templates_show();//展示模板集

    void temp_function();   //临时函数

    void on_capture_clicked();  //按下捕获按钮

    void on_clear_templates_clicked();  //按下清除模板按钮

    void on_test_clicked();     //测试按钮

protected:
    void closeEvent(QCloseEvent *event) override;   //重写关闭事件


private:
    Ui::MainWindow *ui;

    QString result;

    cv::Mat frame;                      //摄像头使用
    std::vector<cv::Mat> img_template;   //用于存储模板图像
    cv::VideoCapture capture;
    std::string camera_IP, camera_port;
    cv::Mat frame_temp;                 //拍照时使用
//    int num = 0;

    ip_camera_setting *ip_camera_setting_widget;

    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;

    QTimer *camera_timer;

//    color_detector *col_detector;

    double template_num = 0;
//    angle_detector *agl_detector;

//    Angle_detector *a;

    double temp0 = 0;
    double temp1 = 4;
    img_template_widget *itw;

};
#endif // MAINWINDOW_H
