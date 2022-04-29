#ifndef WIDGET_H
#define WIDGET_H

#include "client_connection.h"

#include <QWidget>
#include <QTableView>
#include <QStandardItem>
#include <QList>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void starting_the_request();

public slots:
    void cell_clicked(const QModelIndex &index);

private:
    MyClient client;
    Ui::Widget *ui;
    QTableView table;
    int pic_i=0;

    void next_pic();
    void prev_pic();
    void load_pic(int index);
    void pre_load_pic_0();
    void load_pic_0();
    void Length(int l);
    void load_complete();

    int count = 0;

    QVector <QList <QStandardItem *>> items_list;
    QStandardItem *item = new QStandardItem();
};
#endif // WIDGET_H
