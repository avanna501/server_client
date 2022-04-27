#include "widget.h"
#include "ui_widget.h"
#include "client_connection.h"
#include <QObject>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton_getURLs, &QPushButton::clicked,[this]{   starting_the_request();
                                                                    ui->next_Button->setDisabled(true);
                                                                    ui->previous_Button->setDisabled(true);});
    connect(ui->next_Button,&QPushButton::clicked,this,&Widget::next_pic);
    connect(ui->previous_Button,&QPushButton::clicked,this,&Widget::prev_pic);
};
Widget::~Widget()
{
    delete ui;
}

void Widget::starting_the_request()
{
    qInfo()<<"I'm in function sender";
    QString l=ui->server_ip_line->text();
    client.request(l);

    connect(&client,&MyClient::created,this,&Widget::pre_load_pic_0);
}

void Widget::next_pic()
{
    i=(i+client.vdownloader.size()+1)%client.vdownloader.size();
    qInfo()<<"next"<<i;
    load_pic(client.vdownloader[i].file_name);
}

void Widget::prev_pic()
{
    i=(i+client.vdownloader.size()-1)%client.vdownloader.size();
    qInfo()<<"previous"<<i;
    load_pic(client.vdownloader[i].file_name);
}

void Widget::load_pic(QString path)
{
    QPixmap pic(path);
    ui->pic_label->setPixmap(pic.scaled(ui->pic_label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Widget::pre_load_pic_0()
{
    connect(&client.vdownloader[0],&Downloader::done_0,this,&Widget::load_pic_0);
}

void Widget::load_pic_0()
{
    QPixmap pic;
    pic.load(client.vdownloader[0].file_name);
    ui->pic_label->setPixmap(pic.scaled(ui->pic_label->size(),
                                         Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation));
    ui->previous_Button->setEnabled(true);
    ui->next_Button->setEnabled(true);
}
