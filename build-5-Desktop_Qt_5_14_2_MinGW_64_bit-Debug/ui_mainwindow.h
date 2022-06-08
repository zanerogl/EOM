/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionLocal_Camera;
    QAction *actionIP_Camera;
    QAction *actionQuit;
    QAction *actionLogout;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QLabel *screen;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QPushButton *capture;
    QPushButton *clear_templates;
    QSpinBox *num_of_tem;
    QLabel *label_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QTextBrowser *log;
    QLabel *original_image;
    QSpinBox *port;
    QLabel *captured_image;
    QPushButton *test;
    QPushButton *Server_startup;
    QPushButton *clear_button;
    QPushButton *quit_button;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menuSetting;
    QMenu *menuCamera;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1050, 650);
        MainWindow->setMinimumSize(QSize(1050, 650));
        MainWindow->setMaximumSize(QSize(1050, 650));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QFont font;
        font.setFamily(QString::fromUtf8("Corbel"));
        actionAbout->setFont(font);
        actionLocal_Camera = new QAction(MainWindow);
        actionLocal_Camera->setObjectName(QString::fromUtf8("actionLocal_Camera"));
        actionLocal_Camera->setFont(font);
        actionIP_Camera = new QAction(MainWindow);
        actionIP_Camera->setObjectName(QString::fromUtf8("actionIP_Camera"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionLogout = new QAction(MainWindow);
        actionLogout->setObjectName(QString::fromUtf8("actionLogout"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        screen = new QLabel(widget_2);
        screen->setObjectName(QString::fromUtf8("screen"));
        screen->setMinimumSize(QSize(640, 480));
        screen->setMaximumSize(QSize(640, 480));
        screen->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"background-color: rgba(0, 0, 0, 95);\n"
""));

        gridLayout_2->addWidget(screen, 0, 0, 1, 1);

        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        capture = new QPushButton(widget_3);
        capture->setObjectName(QString::fromUtf8("capture"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Corbel"));
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        capture->setFont(font1);
        capture->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(capture, 2, 2, 1, 1);

        clear_templates = new QPushButton(widget_3);
        clear_templates->setObjectName(QString::fromUtf8("clear_templates"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Corbel"));
        font2.setPointSize(11);
        clear_templates->setFont(font2);
        clear_templates->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(clear_templates, 2, 3, 1, 1);

        num_of_tem = new QSpinBox(widget_3);
        num_of_tem->setObjectName(QString::fromUtf8("num_of_tem"));
        num_of_tem->setMinimumSize(QSize(0, 0));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Corbel"));
        font3.setPointSize(9);
        num_of_tem->setFont(font3);
        num_of_tem->setLayoutDirection(Qt::LeftToRight);
        num_of_tem->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        num_of_tem->setMaximum(8);
        num_of_tem->setStepType(QAbstractSpinBox::DefaultStepType);
        num_of_tem->setValue(0);

        gridLayout_3->addWidget(num_of_tem, 2, 1, 1, 1);

        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Corbel"));
        font4.setPointSize(10);
        label_2->setFont(font4);

        gridLayout_3->addWidget(label_2, 0, 1, 1, 1);


        gridLayout_2->addWidget(widget_3, 1, 0, 1, 1);


        horizontalLayout->addWidget(widget_2);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        log = new QTextBrowser(widget);
        log->setObjectName(QString::fromUtf8("log"));
        QFont font5;
        font5.setFamily(QString::fromUtf8("DengXian"));
        font5.setPointSize(10);
        log->setFont(font5);

        gridLayout->addWidget(log, 4, 0, 1, 2);

        original_image = new QLabel(widget);
        original_image->setObjectName(QString::fromUtf8("original_image"));
        original_image->setMinimumSize(QSize(160, 120));
        original_image->setMaximumSize(QSize(160, 120));
        original_image->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"background-color: rgba(0, 0, 0, 95);\n"
""));

        gridLayout->addWidget(original_image, 0, 0, 1, 1);

        port = new QSpinBox(widget);
        port->setObjectName(QString::fromUtf8("port"));
        port->setFont(font5);
        port->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        port->setMinimum(1000);
        port->setMaximum(99999);
        port->setValue(1000);

        gridLayout->addWidget(port, 2, 0, 1, 1);

        captured_image = new QLabel(widget);
        captured_image->setObjectName(QString::fromUtf8("captured_image"));
        captured_image->setMinimumSize(QSize(160, 120));
        captured_image->setMaximumSize(QSize(160, 120));
        captured_image->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"background-color: rgba(0, 0, 0, 95);\n"
""));

        gridLayout->addWidget(captured_image, 0, 1, 1, 1);

        test = new QPushButton(widget);
        test->setObjectName(QString::fromUtf8("test"));
        test->setFont(font4);
        test->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(test, 9, 0, 1, 2);

        Server_startup = new QPushButton(widget);
        Server_startup->setObjectName(QString::fromUtf8("Server_startup"));
        Server_startup->setFont(font4);
        Server_startup->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(Server_startup, 2, 1, 1, 1);

        clear_button = new QPushButton(widget);
        clear_button->setObjectName(QString::fromUtf8("clear_button"));
        clear_button->setFont(font4);
        clear_button->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(clear_button, 6, 0, 1, 2);

        quit_button = new QPushButton(widget);
        quit_button->setObjectName(QString::fromUtf8("quit_button"));
        quit_button->setFont(font4);
        quit_button->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(quit_button, 7, 0, 1, 2);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font6;
        font6.setFamily(QString::fromUtf8("DengXian"));
        label->setFont(font6);

        gridLayout->addWidget(label, 1, 0, 1, 1);


        horizontalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1050, 26));
        menuSetting = new QMenu(menubar);
        menuSetting->setObjectName(QString::fromUtf8("menuSetting"));
        menuCamera = new QMenu(menuSetting);
        menuCamera->setObjectName(QString::fromUtf8("menuCamera"));
        menuCamera->setFont(font);
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuSetting->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuSetting->addAction(menuCamera->menuAction());
        menuCamera->addAction(actionLocal_Camera);
        menuCamera->addSeparator();
        menuCamera->addAction(actionIP_Camera);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionLocal_Camera->setText(QCoreApplication::translate("MainWindow", "Local Camera", nullptr));
        actionIP_Camera->setText(QCoreApplication::translate("MainWindow", "IP Camera", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        actionLogout->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
        screen->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
        capture->setText(QCoreApplication::translate("MainWindow", "Capture", nullptr));
        clear_templates->setText(QCoreApplication::translate("MainWindow", "Clear templates", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Number of templates", nullptr));
        log->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DengXian'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'DS ISO 1'; font-size:12pt;\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'DS ISO 1'; font-size:12pt;\"><br /></p></body></html>", nullptr));
        original_image->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
        captured_image->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
        test->setText(QCoreApplication::translate("MainWindow", "Test", nullptr));
        Server_startup->setText(QCoreApplication::translate("MainWindow", "Server startup", nullptr));
        clear_button->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        quit_button->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        menuSetting->setTitle(QCoreApplication::translate("MainWindow", "Setting", nullptr));
        menuCamera->setTitle(QCoreApplication::translate("MainWindow", "Camera", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
