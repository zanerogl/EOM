#include "mainwindow.h"
#include "img_template_widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    img_template_widget itw;
//    itw.show();
    MainWindow w;
    w.show();

//    double num = 10;
//    double num1 = 4;

//    qDebug()<<num/num1;

    return a.exec();
}
