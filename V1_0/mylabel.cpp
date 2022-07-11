#include "mylabel.h"

mylabel::mylabel(QWidget *parent) : QLabel(parent)
{

}

//鼠标按下后
void mylabel::mousePressEvent(QMouseEvent *ev)
{
    emit is_clicked();
    qDebug()<<"clicked.";
}
