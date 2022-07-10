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

private:
    Ui::ip_camera_setting *ui;
};

#endif // IP_CAMERA_SETTING_H
