/********************************************************************************
** Form generated from reading UI file 'img_template_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMG_TEMPLATE_WIDGET_H
#define UI_IMG_TEMPLATE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_img_template_widget
{
public:
    QGridLayout *gridLayout;
    QPushButton *previous;
    QPushButton *next;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *img_template_widget)
    {
        if (img_template_widget->objectName().isEmpty())
            img_template_widget->setObjectName(QString::fromUtf8("img_template_widget"));
        img_template_widget->resize(400, 300);
        gridLayout = new QGridLayout(img_template_widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        previous = new QPushButton(img_template_widget);
        previous->setObjectName(QString::fromUtf8("previous"));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier New"));
        font.setPointSize(10);
        previous->setFont(font);

        gridLayout->addWidget(previous, 1, 1, 1, 1);

        next = new QPushButton(img_template_widget);
        next->setObjectName(QString::fromUtf8("next"));
        next->setFont(font);

        gridLayout->addWidget(next, 1, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 4, 1, 1);

        graphicsView = new QGraphicsView(img_template_widget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 5);


        retranslateUi(img_template_widget);

        QMetaObject::connectSlotsByName(img_template_widget);
    } // setupUi

    void retranslateUi(QWidget *img_template_widget)
    {
        img_template_widget->setWindowTitle(QCoreApplication::translate("img_template_widget", "Form", nullptr));
        previous->setText(QCoreApplication::translate("img_template_widget", "<-", nullptr));
        next->setText(QCoreApplication::translate("img_template_widget", "->", nullptr));
    } // retranslateUi

};

namespace Ui {
    class img_template_widget: public Ui_img_template_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMG_TEMPLATE_WIDGET_H
