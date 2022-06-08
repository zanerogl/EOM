/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QLabel *avatar;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QLineEdit *username;
    QLineEdit *password;
    QLabel *label_2;
    QPushButton *register_2;
    QLabel *label;
    QPushButton *login_2;
    QSpacerItem *verticalSpacer;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout;
    QLabel *warning;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QString::fromUtf8("login"));
        login->resize(250, 450);
        login->setMinimumSize(QSize(250, 450));
        login->setMaximumSize(QSize(250, 450));
        gridLayout = new QGridLayout(login);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QWidget(login);
        widget->setObjectName(QString::fromUtf8("widget"));
        avatar = new QLabel(widget);
        avatar->setObjectName(QString::fromUtf8("avatar"));
        avatar->setGeometry(QRect(9, 9, 211, 141));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        widget_2 = new QWidget(login);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        username = new QLineEdit(widget_2);
        username->setObjectName(QString::fromUtf8("username"));
        QFont font;
        font.setFamily(QString::fromUtf8("Corbel"));
        font.setPointSize(10);
        username->setFont(font);

        gridLayout_2->addWidget(username, 1, 1, 1, 1);

        password = new QLineEdit(widget_2);
        password->setObjectName(QString::fromUtf8("password"));
        password->setFont(font);
        password->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(password, 3, 1, 1, 1);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout_2->addWidget(label_2, 2, 1, 1, 1);

        register_2 = new QPushButton(widget_2);
        register_2->setObjectName(QString::fromUtf8("register_2"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Corbel"));
        font1.setPointSize(12);
        register_2->setFont(font1);
        register_2->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_2->addWidget(register_2, 5, 1, 1, 1);

        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout_2->addWidget(label, 0, 1, 1, 1);

        login_2 = new QPushButton(widget_2);
        login_2->setObjectName(QString::fromUtf8("login_2"));
        login_2->setFont(font1);
        login_2->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_2->addWidget(login_2, 4, 1, 1, 1);

        verticalSpacer = new QSpacerItem(0, 80, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer, 6, 0, 1, 1);

        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout = new QVBoxLayout(widget_3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        warning = new QLabel(widget_3);
        warning->setObjectName(QString::fromUtf8("warning"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Corbel"));
        font2.setPointSize(11);
        warning->setFont(font2);
        warning->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(warning);


        gridLayout_2->addWidget(widget_3, 6, 1, 1, 1);


        gridLayout->addWidget(widget_2, 1, 0, 1, 1);


        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Form", nullptr));
        avatar->setText(QString());
        username->setText(QString());
        password->setText(QString());
        label_2->setText(QCoreApplication::translate("login", "Password", nullptr));
        register_2->setText(QCoreApplication::translate("login", "Register", nullptr));
        label->setText(QCoreApplication::translate("login", "Username", nullptr));
        login_2->setText(QCoreApplication::translate("login", "Login", nullptr));
#if QT_CONFIG(tooltip)
        warning->setToolTip(QCoreApplication::translate("login", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        warning->setWhatsThis(QCoreApplication::translate("login", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        warning->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
