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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include <mylabel.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLocal_Camera;
    QAction *actionIP_Camera;
    QAction *actionAbout;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QWidget *widget_3;
    QGridLayout *gridLayout_4;
    QSpinBox *num_of_tem;
    QProgressBar *progressBar;
    QPushButton *capture;
    QPushButton *clear_templates;
    QLabel *label_0;
    QLabel *label1;
    QLabel *screen;
    QWidget *widget_2;
    QGridLayout *gridLayout_3;
    mylabel *template_image;
    QPushButton *clear_button;
    QTextBrowser *log;
    QPushButton *server_startup;
    QLabel *label_4;
    QSpinBox *port;
    QLabel *captured_image;
    QPushButton *quit_button;
    QPushButton *test;
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
        actionLocal_Camera = new QAction(MainWindow);
        actionLocal_Camera->setObjectName(QString::fromUtf8("actionLocal_Camera"));
        actionIP_Camera = new QAction(MainWindow);
        actionIP_Camera->setObjectName(QString::fromUtf8("actionIP_Camera"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_4 = new QGridLayout(widget_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        num_of_tem = new QSpinBox(widget_3);
        num_of_tem->setObjectName(QString::fromUtf8("num_of_tem"));
        QFont font;
        font.setFamily(QString::fromUtf8("DengXian"));
        font.setPointSize(11);
        num_of_tem->setFont(font);
        num_of_tem->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        num_of_tem->setMaximum(8);

        gridLayout_4->addWidget(num_of_tem, 3, 0, 1, 1);

        progressBar = new QProgressBar(widget_3);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(240, 15));
        progressBar->setMaximumSize(QSize(240, 15));
        QFont font1;
        font1.setFamily(QString::fromUtf8("DengXian"));
        font1.setPointSize(12);
        progressBar->setFont(font1);
        progressBar->setValue(0);

        gridLayout_4->addWidget(progressBar, 1, 1, 1, 1);

        capture = new QPushButton(widget_3);
        capture->setObjectName(QString::fromUtf8("capture"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Corbel"));
        font2.setPointSize(11);
        capture->setFont(font2);
        capture->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_4->addWidget(capture, 3, 1, 1, 1);

        clear_templates = new QPushButton(widget_3);
        clear_templates->setObjectName(QString::fromUtf8("clear_templates"));
        clear_templates->setFont(font2);
        clear_templates->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_4->addWidget(clear_templates, 3, 2, 1, 1);

        label_0 = new QLabel(widget_3);
        label_0->setObjectName(QString::fromUtf8("label_0"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Corbel"));
        font3.setPointSize(10);
        label_0->setFont(font3);

        gridLayout_4->addWidget(label_0, 1, 0, 1, 1);

        label1 = new QLabel(widget_3);
        label1->setObjectName(QString::fromUtf8("label1"));

        gridLayout_4->addWidget(label1, 1, 2, 1, 1);


        gridLayout_2->addWidget(widget_3, 2, 2, 1, 1);

        screen = new QLabel(widget);
        screen->setObjectName(QString::fromUtf8("screen"));
        screen->setMinimumSize(QSize(640, 480));
        screen->setMaximumSize(QSize(640, 480));
        screen->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"background-color: rgba(0, 0, 0, 200);\n"
""));

        gridLayout_2->addWidget(screen, 1, 2, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_3 = new QGridLayout(widget_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        template_image = new mylabel(widget_2);
        template_image->setObjectName(QString::fromUtf8("template_image"));
        template_image->setMinimumSize(QSize(160, 120));
        template_image->setMaximumSize(QSize(160, 120));
        template_image->setCursor(QCursor(Qt::PointingHandCursor));
        template_image->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"background-color: rgba(0, 0, 0, 200);\n"
""));

        gridLayout_3->addWidget(template_image, 0, 1, 1, 1);

        clear_button = new QPushButton(widget_2);
        clear_button->setObjectName(QString::fromUtf8("clear_button"));
        clear_button->setFont(font3);
        clear_button->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(clear_button, 10, 1, 1, 1);

        log = new QTextBrowser(widget_2);
        log->setObjectName(QString::fromUtf8("log"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("DengXian"));
        font4.setPointSize(10);
        log->setFont(font4);

        gridLayout_3->addWidget(log, 6, 1, 1, 2);

        server_startup = new QPushButton(widget_2);
        server_startup->setObjectName(QString::fromUtf8("server_startup"));
        server_startup->setFont(font3);
        server_startup->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(server_startup, 5, 2, 1, 1);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font3);

        gridLayout_3->addWidget(label_4, 4, 1, 1, 1);

        port = new QSpinBox(widget_2);
        port->setObjectName(QString::fromUtf8("port"));
        port->setFont(font4);
        port->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        port->setMinimum(1000);
        port->setMaximum(99999);

        gridLayout_3->addWidget(port, 5, 1, 1, 1);

        captured_image = new QLabel(widget_2);
        captured_image->setObjectName(QString::fromUtf8("captured_image"));
        captured_image->setMinimumSize(QSize(160, 120));
        captured_image->setMaximumSize(QSize(160, 120));
        captured_image->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"background-color: rgba(0, 0, 0, 200);\n"
""));

        gridLayout_3->addWidget(captured_image, 0, 2, 1, 1);

        quit_button = new QPushButton(widget_2);
        quit_button->setObjectName(QString::fromUtf8("quit_button"));
        quit_button->setFont(font3);
        quit_button->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(quit_button, 10, 2, 1, 1);

        test = new QPushButton(widget_2);
        test->setObjectName(QString::fromUtf8("test"));
        test->setFont(font3);
        test->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(test, 11, 1, 1, 2);


        gridLayout->addWidget(widget_2, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1050, 26));
        menuSetting = new QMenu(menubar);
        menuSetting->setObjectName(QString::fromUtf8("menuSetting"));
        menuCamera = new QMenu(menuSetting);
        menuCamera->setObjectName(QString::fromUtf8("menuCamera"));
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
        actionLocal_Camera->setText(QCoreApplication::translate("MainWindow", "Local Camera", nullptr));
        actionIP_Camera->setText(QCoreApplication::translate("MainWindow", "IP Camera", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        capture->setText(QCoreApplication::translate("MainWindow", "Capture", nullptr));
        clear_templates->setText(QCoreApplication::translate("MainWindow", "Clear templates", nullptr));
        label_0->setText(QCoreApplication::translate("MainWindow", "Number of templates", nullptr));
        label1->setText(QString());
        screen->setText(QString());
        template_image->setText(QString());
        clear_button->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        log->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DengXian'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        server_startup->setText(QCoreApplication::translate("MainWindow", "Server startup", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        captured_image->setText(QString());
        quit_button->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        test->setText(QCoreApplication::translate("MainWindow", "Test", nullptr));
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
