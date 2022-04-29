#include "widget.h"
#include "ui_widget.h"
#include "client_connection.h"
#include <QObject>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
//    ui->next_Button->setDisabled(true);
//    ui->previous_Button->setDisabled(true);
    connect(ui->pushButton_getURLs, &QPushButton::clicked,[this]{starting_the_request();});
//                                                                    ui->next_Button->setDisabled(true);
//                                                                    ui->previous_Button->setDisabled(true);
//    connect(ui->next_Button,&QPushButton::clicked,this,&Widget::next_pic);
//    connect(ui->previous_Button,&QPushButton::clicked,this,&Widget::prev_pic);
//    ui->table->setAttribute()

};
Widget::~Widget(){ delete ui; }

void Widget::starting_the_request()
{
    client.request((QString)ui->server_ip_line->text());
    ui->table->setColumnCount(3);
    connect(&client,&MyClient::created,this,&Widget::L);
    qInfo()<<client.lines.size();

    ui->table->gridStyle();
    connect(&client,&MyClient::created,this,&Widget::pre_load_pic_0);
}

void Widget::L(int l)
{
    ui->table->setRowCount((l+2)/3);
}


//void Widget::next_pic()
//{
//    pic_i=(pic_i+client.vdownloader.size()+1)%client.vdownloader.size();
//    load_pic(client.vdownloader[pic_i].file_name);
//}

//void Widget::prev_pic()
//{
//    pic_i=(pic_i+client.vdownloader.size()-1)%client.vdownloader.size();
//    load_pic(client.vdownloader[pic_i].file_name);
//}

void Widget::pre_load_pic_0()
{
    connect(&client.vdownloader[0],&Downloader::done,this,&Widget::load_pic_0);
//    connect(&client.vdownloader[i],&Downloader::done,[this,i]{load_pic(i,client.vdownloader[i].file_name);});
//    connect(&client.vdownloader,&Downloader::done,this,&Widget::load_pic);
}
//
////void Widget::load_pic(int index, QString path)
////{
////    QPixmap pic(path);
////    int d=index;
////    ui->pic_label->setPixmap(pic.scaled(ui->pic_label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
////}
///

void Widget::load_pic(int index)
{
    QPixmap pic;
    pic.load(client.vdownloader[index].file_name);
}

void Widget::load_pic_0()
{
    QPixmap pic;
    pic.load(client.vdownloader[0].file_name);
//    ui->table->setPixmap(pic.scaled(ui->pic_label));
//    ui->table->setItem(0,0,/*pic.scaled(ui->table->size(),
//                                                                              Qt::KeepAspectRatio,
//                                                                              Qt::SmoothTransformation)*/"0");
    ui->pic_label->setPixmap(pic.scaled(ui->pic_label->size(),
                                         Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation));
//    ui->previous_Button->setEnabled(true);
//    ui->next_Button->setEnabled(true);

}
