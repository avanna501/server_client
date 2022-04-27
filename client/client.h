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

    QString line;
    void request(QString server_ip);

    void read();

    QHostInfo hostIP;
    QTcpSocket * tcp=new QTcpSocket(this);
    QList<QString> list;
    QVector<Downloader> qd;
    QDataStream in;

};

#endif // CLIENT_CONNECTION_H
