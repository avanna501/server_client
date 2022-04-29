#include "widget.h"
#include "ui_widget.h"
#include "client_connection.h"

#include <QObject>
#include <QVariant>
#include <QModelIndex>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton_getURLs, &QPushButton::clicked,[this]{starting_the_request();});
};

Widget::~Widget(){ delete ui; }

void Widget::starting_the_request()
{
    client.request((QString)ui->server_ip_line->text());
    connect(&client,&MyClient::created,this,&Widget::Length);
    connect(&client,&MyClient::created,this,&Widget::pre_load_pic_0);
}

void Widget::Length(int l)
{
    count=l;
    items_list.resize((l+2)/3);
    for(int i=0;i<(l+2)/3;i++) items_list[i] << nullptr << nullptr << nullptr;
    for(int i=0;i<l;i++) connect(&client.vdownloader[i],&Downloader::done,this,&Widget::load_pic);
}

void Widget::load_pic(int index)
{
    int col=index%3;
    int row=index/3;

    QPixmap pic;
    pic.load(client.vdownloader[index].file_name);
    pic=pic.scaled(75 ,100, Qt::KeepAspectRatioByExpanding,
                            Qt::SmoothTransformation);

    QStandardItem *item = new QStandardItem();
    item->setData(QVariant(pic), Qt::DecorationRole);

    switch(col)
    {
    case 0:
        items_list[row].removeFirst();
        items_list[row].prepend(item);
        break;
    case 1:
        items_list[row].removeAt(1);
        items_list[row].insert(1,item);
        break;
    case 2:
        items_list[row].removeLast();
        items_list[row].append(item);
        break;
    }

    count--;
    if (count==0)
        load_complete();
}

void Widget::load_complete()
{
    QStandardItemModel *model;
    model=new QStandardItemModel();
    for (int i = 0; i<items_list.length();i++)
        model->insertRow(i,items_list[i]);
    ui->table->setModel( model );
//    for(int i=0;i<3;i++)
//        ui->table->setColumnWidth(i,100);
//    for(int i=0;i<items_list.length();i++)
//        ui->table->setRowHeight(i,75);
    ui->table->resizeRowsToContents();
    connect(ui->table, SIGNAL(clicked(const QModelIndex&)), this, SLOT(cell_clicked(const QModelIndex&)));

//    connect(ui->table,&QTableView::clicked,this,&Widget::cell_clicked);
}
///////then
///////void MainWindow::recordSelected()
///////{
///////   QModelIndex index = view->currentIndex();
///////   QSqlRecord record;
///////   int i = index.row(); // now you know which record was selected
///////   record = model->record(i);
///////// and I do something with the record
///////}

void Widget::cell_clicked(const QModelIndex &index)
{

    QPixmap pic;
//
//    QModelIndex indexn = ui->table->currentIndex();
    int index_n=3*index.row()+index.column();
    qInfo()<<index_n<<index;

    pic.load(client.vdownloader[index_n].file_name);
    ui->pic_label->setPixmap(pic.scaled(ui->pic_label->size(),
                                         Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation));
}

void Widget::pre_load_pic_0()
{
    connect(&client.vdownloader[0],&Downloader::done,this,&Widget::load_pic_0);
}


void Widget::load_pic_0()
{
    QPixmap pic;
    pic.load(client.vdownloader[0].file_name);
    ui->pic_label->setPixmap(pic.scaled(ui->pic_label->size(),
                                         Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation));
}
