#include "client_connection.h"
#include "download.h"
#include "widget.h"

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QComboBox>
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QDialogButtonBox>
#include <QGuiApplication>
#include <QGroupBox>
#include <QTimer>
#include <QMessageBox>
#include <QStyleHints>
#include <QHostAddress>

MyClient::MyClient()
{
    qInfo()<<"I'm in the constructor of MyClass";
//    connect(tcp, &QTcpSocket::readyRead,this,&MyClient::read);
//   connect(tcp, &QTcpSocket::connected,this,&MyClient::handleSocketConnected);
}
MyClient::~MyClient(){
    qInfo()<<"MyClient is destroyed";
}

void MyClient::handleSocketConnected()
{
    in.setDevice(tcp);
    in.setVersion(QDataStream::Qt_4_0);
}

void MyClient::request(QString server_ip)
{
    qInfo()<<"I'm in MyClient.request" << server_ip;
//    QHostAddress ip;
//    ip.setAddress(server_ip);
//    qInfo()<<ip;
    vdownloader.resize(0);          //?????????????????????????????????
    if (!tcp) {
        tcp = new QTcpSocket(this);
        qInfo()<<"new tcpSocket is created";
    }
    if (tcp->state() != QAbstractSocket::UnconnectedState) {
        tcp->disconnectFromHost();
        tcp->waitForDisconnected();
        qInfo()<<"disconnected if any connection";
    }
    tcp->connectToHost(server_ip, 2525);
    qInfo()<<"connected to server";
    connect(tcp, &QTcpSocket::readyRead,this,&MyClient::read);
    connect(tcp, &QTcpSocket::connected,this,&MyClient::handleSocketConnected);

}

void MyClient::read()
{
    qInfo()<<"function read";

    in.startTransaction();
    in >> line_of_URLs;
    if (!in.commitTransaction())
        return;

    QStringList lines = line_of_URLs.split("\r\n", Qt::SkipEmptyParts);

    vdownloader.resize(lines.size());
    if (lines.size()>0)
        emit created();
//        connect(&vdownloader[0],&Downloader::done,sender,&Widget::load_pic_0);
    for(int i=0;i<lines.size();i++)
    {
        vdownloader[i].setTarget(lines[i]);
        vdownloader[i].download_request(i);
    }
//    j.setTarget("https://imgs.search.brave.com/G5WicQibCZSFdm80uvWTXxWFH9TaLbowjsQstqJjBUM/rs:fit:1200:1200:1/g:ce/aHR0cDovL3d3dy53/YWxscGFwZXJzMTMu/Y29tL3dwLWNvbnRl/bnQvdXBsb2Fkcy8y/MDE2LzAyL0JlYXV0/aWZ1bC1MYW5kc2Nh/cGUtSEQtV2FsbHBh/cGVyLXdhdGVyLW1v/dW50YWlucy13aXRo/LXNub3ctc2t5LWNs/b3Vkcy1yZWZsZWN0/aW9uLTE5MjB4MTQ0/MC5qcGc");
//    j.download_request(999);
//    tcp->deleteLater();
//    tcp = nullptr;
}
