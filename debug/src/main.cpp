//#include "mainwindow.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    login window;
    window.show();

///    std::tuple<int,int> b = std::make_tuple(2,3);

///    // get函数取值
///    std::get<0>(b);//2
///    std::get<1>(b);//3

///    // std::make_tuple取值
///    int m,n;

///    // std::ref(...)把变量提升为左值引用 int&
///    std::make_tuple(std::ref(m),std::ref(n))=b;// m=2,n=3



    return a.exec();
}
