#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "download.h"
#include <QTcpSocket>
#include <QHostInfo>
#include <QDataStream>
#include <QString>
#include <QList>
#include <QVector>


class MyClient : public QObject
{
    Q_OBJECT

public:
    MyClient();
    ~MyClient();

    void request(QString server_ip);
    void read();

    QString line_of_URLs;
    QTcpSocket * tcp=new QTcpSocket(this);

    QDataStream in;

    QList<QString> list;
    QVector<Downloader> vdownloader;
    Downloader j;
};

#endif // CLIENT_CONNECTION_H
