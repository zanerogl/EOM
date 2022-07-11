/************************************************************/
/************************************************************/
/*****      Author: Zanerogl                            *****/
/*****      email:  z534214462@gmail.com                *****/
/*****      Blog:   https://zanerogl.github.io/         *****/
/*****      Github:https://github.com/zanerogl          *****/
/************************************************************/
/************************************************************/

#ifndef IP_CAMERA_SETTING_H
#define IP_CAMERA_SETTING_H

#include <QWidget>

namespace Ui {
class ip_camera_setting;
}

class ip_camera_setting : public QWidget
{
    Q_OBJECT

public:
    explicit ip_camera_setting(QWidget *parent = nullptr);
    ~ip_camera_setting();

signals:
    void send(std::string address, std::string port);   //点击connect，发送信号

private slots:
    void on_connect_button_clicked();

    void on_cancel_button_clicked();

private:
    Ui::ip_camera_setting *ui;
};

#endif // IP_CAMERA_SETTING_H
