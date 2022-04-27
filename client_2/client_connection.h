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
    QVector<Downloader> vdownloader;

public slots:
    void read();

private:
    QString line_of_URLs;
    QTcpSocket * tcp = new QTcpSocket(this);
    void handleSocketConnected();
    QDataStream in;
    QList<QString> list;

signals:
    void created();
};

#endif // CLIENT_CONNECTION_H
