/********************************************************************************
** Form generated from reading UI file 'ip_camera_setting.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IP_CAMERA_SETTING_H
#define UI_IP_CAMERA_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ip_camera_setting
{
public:

    void setupUi(QWidget *ip_camera_setting)
    {
        if (ip_camera_setting->objectName().isEmpty())
            ip_camera_setting->setObjectName(QString::fromUtf8("ip_camera_setting"));
        ip_camera_setting->resize(400, 300);

        retranslateUi(ip_camera_setting);

        QMetaObject::connectSlotsByName(ip_camera_setting);
    } // setupUi

    void retranslateUi(QWidget *ip_camera_setting)
    {
        ip_camera_setting->setWindowTitle(QCoreApplication::translate("ip_camera_setting", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ip_camera_setting: public Ui_ip_camera_setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IP_CAMERA_SETTING_H
