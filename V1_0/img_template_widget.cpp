#include "img_template_widget.h"
#include "ui_img_template_widget.h"

img_template_widget::img_template_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::img_template_widget)
{
    ui->setupUi(this);
    /*阻塞当前窗口*/
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("1");
    ui->previous->setDisabled(true);    //先禁用上一页
    qDebug()<<"Img_templates_size: "<<img_templates_size;
    if(img_templates_size == 1){
        ui->next->setDisabled(true);
    }
}

//img_template_widget::img_template_widget(std::vector<QImage> img_templates_qt_out):ui(new Ui::img_template_widget)
//{
//    qDebug()<<img_templates_qt_out.size();
//    img_templates_qt = img_templates_qt_out;
//    img_templates_size = img_templates_qt.size();
//}

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
        img_templates_qt.push_back(img);

        /*此句有BUG，若不用临时变量来赋值会导致最终容器中只能存size()张第一张图
        img_templates.push_back(QImage((const uchar*)cv_img_templates.at(i).data, cv_img_templates.at(i).cols, cv_img_templates.at(i).rows, QImage::Format_RGB888).rgbSwapped());
        */
    }
    img_templates_size = img_templates_qt.size();
}

//展示图片
void img_template_widget::img_dispaly(int x)
{
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    scene->addPixmap(QPixmap::fromImage(img_templates_qt.at(x)));
}

//按下下一张按钮
void img_template_widget::on_next_clicked()
{
    if( (unsigned long long)pages+1 < img_templates_size ){
        ++pages;
        qDebug()<<"Pages: "<<pages;
        img_dispaly(pages);
        ui->previous->setEnabled(true);
        this->setWindowTitle(QString::number(pages+1));
        if((unsigned long long)pages+1 == img_templates_size){
            ui->next->setDisabled(true);    //禁用按钮
        }
    }
}

//按下上一张按钮
void img_template_widget::on_previous_clicked()
{
    ui->next->setEnabled(true);
    if(pages > 0){
        --pages;
        img_dispaly(pages);
        this->setWindowTitle(QString::number(pages+1));
        if(pages-1 < 0){
            ui->previous->setDisabled(true);    //禁用按钮
        }
        qDebug()<<"Pages: "<<pages;
    }
}
