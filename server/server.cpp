#include "server.h"
#include <QDebug>
#include <>

MyServer::MyServer()
{
    read();
    if (!list.isEmpty() && listen(QHostAddress::Any, 45555))
    {
        qInfo() << "Server Started";
       connect(this, &QTcpServer::newConnection, this, &MyServer::incoming_connection);
    }

    else
        qInfo() << "Error starting server or empty file";

}

void MyServer::read()
{

    QFile file(file_name);
    if (!file.exists())
    {
        qDebug()<<"file not found";
        return;
    }

    if (!file.open(QIODevice::OpenModeFlag::ReadOnly))
    {
        qDebug()<<"couldn't open the file";
        return;
    }
    while(!file.atEnd())
        list.append(file.readLine());
 }

void MyServer::incoming_connection()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

        out << list[QRandomGenerator::global()->bounded(fortunes.size())];
    QDataStream out(&exchanging_data, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_5_10);

    out << list;

    soc = this->nextPendingConnection();
    connect(soc, &QAbstractSocket::disconnected, soc, &QObject::deleteLater);

    soc->write(data);
    soc->disconnectFromHost();
}
