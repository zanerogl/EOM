#include "ip_camera_setting.h"
#include "ui_ip_camera_setting.h"

ip_camera_setting::ip_camera_setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ip_camera_setting)
{
    ui->setupUi(this);
}

ip_camera_setting::~ip_camera_setting()
{
    delete ui;
}
