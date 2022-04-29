#ifndef WIDGET_H
#define WIDGET_H

#include "client_connection.h"

#include <QWidget>
#include <QTableView>


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

private:
    MyClient client;
    Ui::Widget *ui;
    QTableView table;
    int pic_i=0;

    void next_pic();
    void prev_pic();
    void load_pic(int index/*, QString path*/);
    void pre_load_pic_0();
    void load_pic_0();
    void L(int l);
};
#endif // WIDGET_H
