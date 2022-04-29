#include "server.h"

#include <QDebug>
#include <QDataStream>
#include <QFile>
#include <QNetworkInterface>
#include <QTcpSocket>


MyServer::MyServer()
{
    read_tosend();
    if (!list.isEmpty() && listen(QHostAddress::Any, 2525))
    {
        qInfo() << "Server Started";
        QString ipAddress;
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
        for (int i = 0; i < ipAddressesList.size(); ++i)
        {
            if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address())
            {
                ipAddress = ipAddressesList.at(i).toString();
                break;
            }
        }
        qInfo() << "server listening on" << ipAddress;
        connect(this, &QTcpServer::newConnection, this, &MyServer::incoming_connection);
    }
    else
    {
        qInfo() << "Error starting server or empty file";
        exit(0);
    }

}

void MyServer::read_tosend()
{
    QString file_name = "list.txt";
    QFile file(file_name);
    if (!file.exists())
    {
        qDebug() << "file not found";
        return;
    }

    if (!file.open(QIODevice::OpenModeFlag::ReadOnly))
    {
        qDebug() << "couldn't open the file";
        return;
    }

    list = file.readAll();
 }

void MyServer::incoming_connection()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out << list;

    QTcpSocket * soc;
    soc = this->nextPendingConnection();
    connect(soc, &QAbstractSocket::disconnected, soc, &QObject::deleteLater);
    qInfo() << "new connection";
    soc->write(data);
}
