#include "widget.h"
#include "ui_widget.h"
#include "client.h"
#include <QObject>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->getURLs_button, &QPushButton::clicked,[this]{starting_the_request();});
};

Widget::~Widget()
{
//    delete ui;
}

void Widget::starting_the_request()
{
    qInfo()<<"I'm in function sender";
    QString l=ui->server_ip->text();
    client.request(l);
}
