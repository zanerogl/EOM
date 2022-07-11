#include "ip_camera_setting.h"
#include "ui_ip_camera_setting.h"
#include <QDebug>
ip_camera_setting::ip_camera_setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ip_camera_setting)
{
    ui->setupUi(this);
    this->setWindowTitle(" ");
    this->setWindowIcon(QIcon(":/res/Zanerogl.png"));
    /*禁用关闭窗口*/
    this->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    /*阻塞当前窗口*/
    this->setWindowModality(Qt::ApplicationModal);

}

ip_camera_setting::~ip_camera_setting()
{
    qDebug()<<"ip_camera_setting is released";
    delete ui;
}

//点击连接，发送信号，信号内容：ip和端口
void ip_camera_setting::on_connect_button_clicked()
{
    emit send(ui->ip_address_edit->text().toStdString(), ui->port_edit->text().toStdString());
    this->close();
    this->~ip_camera_setting();
}

//点击取消，关闭窗口
void ip_camera_setting::on_cancel_button_clicked()
{
    this->close();
    this->~ip_camera_setting();
}
