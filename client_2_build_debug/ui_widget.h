/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *server_ip_line;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_getURLs;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QLabel *pic_label;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *previous_Button;
    QPushButton *next_Button;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(397, 448);
        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(21, 16, 353, 411));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        server_ip_line = new QLineEdit(widget);
        server_ip_line->setObjectName(QString::fromUtf8("server_ip_line"));

        horizontalLayout->addWidget(server_ip_line);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_getURLs = new QPushButton(widget);
        pushButton_getURLs->setObjectName(QString::fromUtf8("pushButton_getURLs"));

        horizontalLayout_2->addWidget(pushButton_getURLs);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(218, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pic_label = new QLabel(widget);
        pic_label->setObjectName(QString::fromUtf8("pic_label"));
        pic_label->setMinimumSize(QSize(351, 271));
        pic_label->setLayoutDirection(Qt::LeftToRight);
        pic_label->setAutoFillBackground(true);
        pic_label->setScaledContents(false);
        pic_label->setAlignment(Qt::AlignCenter);
        pic_label->setWordWrap(false);

        verticalLayout->addWidget(pic_label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        previous_Button = new QPushButton(widget);
        previous_Button->setObjectName(QString::fromUtf8("previous_Button"));

        horizontalLayout_3->addWidget(previous_Button);

        next_Button = new QPushButton(widget);
        next_Button->setObjectName(QString::fromUtf8("next_Button"));

        horizontalLayout_3->addWidget(next_Button);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Widget);
        QObject::connect(pushButton_getURLs, &QPushButton::clicked, pic_label, qOverload<>(&QLabel::clear));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Widget", "Server IP", nullptr));
        pushButton_getURLs->setText(QCoreApplication::translate("Widget", "Get the URLs", nullptr));
        pic_label->setText(QCoreApplication::translate("Widget", "the pictures will be displayed here", nullptr));
        previous_Button->setText(QCoreApplication::translate("Widget", "previous", nullptr));
        next_Button->setText(QCoreApplication::translate("Widget", "next", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
