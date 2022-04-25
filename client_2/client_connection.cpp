#include "client_connection.h"
#include "download.h"


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

MyClient::MyClient(){qInfo()<<"I'm in the constructor of MyClass";}
MyClient::~MyClient(){qInfo()<<"MyClient is destroyed";}

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
    in >> line_of_URLs;
    //    qInfo()<<line_of_URLs;
    if (!in.commitTransaction())
        return;

    QStringList lines = line_of_URLs.split('\n', Qt::SkipEmptyParts);
//    for(int i=0;line_of_URLs.indexOf("\n")>=0;i++)
//    {
//        list.append(line_of_URLs.mid(0, line_of_URLs.toStdString().find("\n")));
//        line_of_URLs=line_of_URLs.mid(line_of_URLs.toStdString().find("\n")+1);
//    }
//    list.append(line_of_URLs);
//    qInfo()<<list;


    vdownloader.resize(lines.size());

    for(int i=0;i<lines.size();i++)
    {
        vdownloader[i].setTarget(lines[i]);
        vdownloader[i].download_request(i);
    }
//    j.setTarget("https://imgs.search.brave.com/G5WicQibCZSFdm80uvWTXxWFH9TaLbowjsQstqJjBUM/rs:fit:1200:1200:1/g:ce/aHR0cDovL3d3dy53/YWxscGFwZXJzMTMu/Y29tL3dwLWNvbnRl/bnQvdXBsb2Fkcy8y/MDE2LzAyL0JlYXV0/aWZ1bC1MYW5kc2Nh/cGUtSEQtV2FsbHBh/cGVyLXdhdGVyLW1v/dW50YWlucy13aXRo/LXNub3ctc2t5LWNs/b3Vkcy1yZWZsZWN0/aW9uLTE5MjB4MTQ0/MC5qcGc");
//    j.download_request(55);
    tcp->deleteLater();
}
