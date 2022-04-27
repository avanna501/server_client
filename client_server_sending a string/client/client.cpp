#include "client.h"
#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
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
#include <QCoreApplication>
#include <QApplication>

Client::Client(QWidget *parent) : QObject(parent)
//    , host(new QLineEdit)
//    , getPictures(new QPushButton(tr("Get URL-s")))
//    , tcpSocket(new QTcpSocket(this))
{
    qInfo()<<"I'm in client constructor";



}

void Client::requestURL()
{
    getPictures->setEnabled(false);
    tcpSocket->abort();

    tcpSocket->connectToHost(host->text(),2525/*portLineEdit->text().toInt()*/);
}

void Client::read()
{
    in.startTransaction();
    in >> line;
    if (!in.commitTransaction())
        return;
    getPictures->setEnabled(true);

}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError: break;
    case QAbstractSocket::HostNotFoundError:     qInfo()<<("The host was not found. Please check the host name and port settings.");
        break;
    case QAbstractSocket::ConnectionRefusedError:qInfo()<<"The connection was refused by the peer. Make sure the fortune server is running, and check that the host name and port settings are correct.";
        break;
    default:        qInfo()<<"The following error occurred: "<<tcpSocket->errorString();
    }
    getPictures->setEnabled(true);
}
