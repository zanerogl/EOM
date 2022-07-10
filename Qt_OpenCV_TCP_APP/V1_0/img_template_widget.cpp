#include "img_template_widget.h"
#include "ui_img_template_widget.h"

img_template_widget::img_template_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::img_template_widget)
{
    ui->setupUi(this);
    /*阻塞当前窗口*/
    this->setWindowModality(Qt::ApplicationModal);

    img_dispaly(0);
}

img_template_widget::~img_template_widget()
{
    delete ui;
}

//存储模板集
void img_template_widget::img_saver(std::vector<cv::Mat> cv_img_templates)
{
    for(unsigned long long i = 0; i < cv_img_templates.size(); i++){
        // 将Mat格式转换为QImage格式，存入容器，QImage::Format_RGB888不同的摄像头用不同的格式
        QImage img = QImage((const uchar*)cv_img_templates.at(i).data, cv_img_templates.at(i).cols, cv_img_templates.at(i).rows, QImage::Format_RGB888).rgbSwapped();
        img_templates.push_back(img);

        /*此句有BUG，若不用临时变量来赋值会导致最终容器中只能存size()张第一张图
        img_templates.push_back(QImage((const uchar*)cv_img_templates.at(i).data, cv_img_templates.at(i).cols, cv_img_templates.at(i).rows, QImage::Format_RGB888).rgbSwapped());
        */
}
    img_templates_size = img_templates.size();
}

//展示图片
void img_template_widget::img_dispaly(int x)
{
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    scene->addPixmap(QPixmap::fromImage(img_templates.at(x)));
}

//按下下一张按钮
void img_template_widget::on_next_clicked()
{
    if(pages < (int)img_templates.size()){
        img_dispaly(pages);
        qDebug()<<"Pages: "<<pages;
        pages++;
    }
}

//按下上一张按钮
void img_template_widget::on_previous_clicked()
{
    if(pages > 0){
        img_dispaly(pages);
        qDebug()<<"Pages: "<<pages;
        pages--;
    }
}
