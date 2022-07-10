#ifndef IMG_TEMPLATE_WIDGET_H
#define IMG_TEMPLATE_WIDGET_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <QImage>
#include <iostream>
#include <QDebug>

namespace Ui {
class img_template_widget;
}

class img_template_widget : public QWidget
{
    Q_OBJECT

public:
    explicit img_template_widget(QWidget *parent = nullptr);
    ~img_template_widget();

    unsigned long long img_templates_size;

    void img_saver(std::vector<cv::Mat> cv_img_templates);   //保存模板集并转换类型

    void img_dispaly(int x);

private slots:
    void on_next_clicked();     //按下下一张按钮

    void on_previous_clicked();

private:
    Ui::img_template_widget *ui;

    std::vector<QImage> img_templates;
//    QImage img_temp;
    int pages = 1;
};

#endif // IMG_TEMPLATE_WIDGET_H
