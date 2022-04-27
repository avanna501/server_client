#include "client.h"
#include "download.h"

#include <QDebug>

#include <QDialog>
#include <QDialogButtonBox>

#include <QGuiApplication>

#include <QGroupBox>

#include <QHostAddress>
#include <QHostInfo>

#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>

#include <QNetworkInterface>

#include <QPushButton>
#include <QStyleHints>
#include <QTimer>

#include <QTcpSocket>
#include <QTcpServer>

#include <QVBoxLayout>

#include <QWidget>


MyClient::MyClient(){qInfo()<<"I'm in the constructor of MyClass";}

void MyClient::request(QString server_ip)
{
    qInfo()<<"I'm in MyClient.request";
    QHostAddress ip;
    ip.setAddress(server_ip);
    qInfo()<<ip;

    tcp->connectToHost(ip,2525);
    in.setDevice(tcp);
    in.setVersion(QDataStream::Qt_4_0);
    connect(tcp, &QTcpSocket::readyRead,this,&MyClient::read);
}

void MyClient::read()
{
    qInfo()<<"function read";

    in.startTransaction();
    in >> line;
    qInfo()<<line;
    if (!in.commitTransaction())
        return;
    int i;
        for(i=0;line.indexOf("\n")>=0;i++)
        {
            list.append(line.mid(0, line.toStdString().find("\n")));
            line=line.mid(line.toStdString().find("\n")+1);
        }
        list.append(line);

        qd.resize(list.size());

        for(;!list.isEmpty();)
        {
            qd[i].setTarget(list.takeAt(0));
            qd[i].download_request(i);
            i++;
        }
    tcp->deleteLater();
}
