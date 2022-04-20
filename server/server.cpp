#include "server.h"
#include <QDebug>
#include <QDataStream>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QNetworkInterface>
#include <QLabel>
#include <QHostInfo>

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

//    QString ipAddress;
//    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
//     // use the first non-localhost IPv4 address
//     for (int i = 0; i < ipAddressesList.size(); ++i) {
//         if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
//             ipAddressesList.at(i).toIPv4Address()) {
//             ipAddress = ipAddressesList.at(i).toString();
//             break;
//         }
//     }
//     // if we did not find one, use IPv4 localhost
//     if (ipAddress.isEmpty())
//         ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
//     statusLabel->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
//                             "Run the Fortune Client example now.")
//                          .arg(ipAddress).arg(MyServer->serverPort()));

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
//    while(!file.atEnd())
//        list.append(file.readLine());
    list=file.readAll();
 }

void MyServer::incoming_connection()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << list;

    soc = this->nextPendingConnection();
    connect(soc, &QAbstractSocket::disconnected, soc, &QObject::deleteLater);
    qInfo()<<"new connection";
    soc->write(data);
    soc->disconnectFromHost();
}

void MyServer::show(int argc, char *argv[])
{
        QApplication app(argc, argv);
        QWidget  window;
        QHostInfo hostInfo;
        qInfo()<<"server IP:"<<hostInfo.localDomainName();

        window.show();
        app.exec();
        return;
}
