#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>
#include <QDebug>

class mylabel : public QLabel
{
    Q_OBJECT
public:
    explicit mylabel(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *ev);

signals:
    void is_clicked();
};

#endif // MYLABEL_H
