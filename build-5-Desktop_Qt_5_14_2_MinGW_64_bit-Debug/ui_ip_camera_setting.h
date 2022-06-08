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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ip_camera_setting
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *connect_button;
    QPushButton *cancel_button;
    QLabel *label_2;
    QLineEdit *ip_address_edit;
    QLineEdit *port_edit;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *ip_camera_setting)
    {
        if (ip_camera_setting->objectName().isEmpty())
            ip_camera_setting->setObjectName(QString::fromUtf8("ip_camera_setting"));
        ip_camera_setting->resize(250, 170);
        ip_camera_setting->setMinimumSize(QSize(250, 170));
        ip_camera_setting->setMaximumSize(QSize(250, 180));
        gridLayout = new QGridLayout(ip_camera_setting);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(ip_camera_setting);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Corbel"));
        font.setPointSize(12);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        widget = new QWidget(ip_camera_setting);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        connect_button = new QPushButton(widget);
        connect_button->setObjectName(QString::fromUtf8("connect_button"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Corbel"));
        font1.setPointSize(11);
        connect_button->setFont(font1);
        connect_button->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(connect_button);

        cancel_button = new QPushButton(widget);
        cancel_button->setObjectName(QString::fromUtf8("cancel_button"));
        cancel_button->setFont(font1);
        cancel_button->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(cancel_button);


        gridLayout->addWidget(widget, 5, 0, 1, 2);

        label_2 = new QLabel(ip_camera_setting);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        ip_address_edit = new QLineEdit(ip_camera_setting);
        ip_address_edit->setObjectName(QString::fromUtf8("ip_address_edit"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("DengXian"));
        font2.setPointSize(10);
        ip_address_edit->setFont(font2);
        ip_address_edit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(ip_address_edit, 0, 1, 1, 1);

        port_edit = new QLineEdit(ip_camera_setting);
        port_edit->setObjectName(QString::fromUtf8("port_edit"));
        port_edit->setFont(font2);
        port_edit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(port_edit, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);


        retranslateUi(ip_camera_setting);

        QMetaObject::connectSlotsByName(ip_camera_setting);
    } // setupUi

    void retranslateUi(QWidget *ip_camera_setting)
    {
        ip_camera_setting->setWindowTitle(QCoreApplication::translate("ip_camera_setting", "Form", nullptr));
        label->setText(QCoreApplication::translate("ip_camera_setting", "IP address :", nullptr));
        connect_button->setText(QCoreApplication::translate("ip_camera_setting", "Connect", nullptr));
        cancel_button->setText(QCoreApplication::translate("ip_camera_setting", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("ip_camera_setting", "Port :", nullptr));
        ip_address_edit->setText(QString());
        port_edit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ip_camera_setting: public Ui_ip_camera_setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IP_CAMERA_SETTING_H
