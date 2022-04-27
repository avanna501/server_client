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

MyClient::MyClient(){ qInfo()<<"I'm in the constructor of MyClass"; }
MyClient::~MyClient(){ qInfo()<<"MyClient is destroyed"; }

void MyClient::handleSocketConnected()
{
    in.setDevice(tcp);
    in.setVersion(QDataStream::Qt_4_0);
}

void MyClient::request(QString server_ip)
{
    qInfo()<<"I'm in MyClient.request" << server_ip;
    vdownloader.clear();
    if (!tcp)
    {
        tcp = new QTcpSocket(this);
        qInfo()<<"new tcpSocket is created";
    }
    if (tcp->state() != QAbstractSocket::UnconnectedState)
    {
        tcp->disconnectFromHost();
        tcp->waitForDisconnected();
        qInfo()<<"disconnected from previous connection";
    }
    tcp->connectToHost(server_ip, 2525);
    connect(tcp, &QTcpSocket::connected,this,&MyClient::handleSocketConnected);
    connect(tcp, &QTcpSocket::readyRead,this,&MyClient::read);
}

void MyClient::read()
{
    in.startTransaction();
    in >> line_of_URLs;
    if (!in.commitTransaction())
        return;
    QStringList lines = line_of_URLs.split("\r\n", Qt::SkipEmptyParts);
    vdownloader.resize(lines.size());
    if (lines.size()>0)
        emit created();
    for(int i=0;i<lines.size();i++)
    {
        vdownloader[i].setTarget(lines[i]);
        vdownloader[i].download_request(i);
    }
}
