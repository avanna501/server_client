#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "download.h"

#include <QDataStream>
#include <QList>
#include <QString>
#include <QTcpSocket>
#include <QVector>


class MyClient : public QObject
{
    Q_OBJECT

public:
    MyClient();
    ~MyClient();

    void request(QString server_ip);

    QStringList lines;
    QVector<Downloader> vdownloader;

private:
    void handleSocketConnected();
    void read();

    QTcpSocket * tcp=new QTcpSocket(this);
    QDataStream in;

signals:
    void created(int);
};

#endif // CLIENT_CONNECTION_H
