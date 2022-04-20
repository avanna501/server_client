#include "client.h"
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


Client::Client(QWidget *parent)
    : QDialog(parent)
    , host(new QLineEdit)
//    , portLineEdit(new QLineEdit)
    , getPictures(new QPushButton(tr("Get URL-s")))
    , tcpSocket(new QTcpSocket(this))
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

//    portLineEdit->setValidator(new QIntValidator(1, 65535, this));
    hostIP.setHostName(host->text());
    auto hostLabel = new QLabel(tr("&Server name:"));
    hostLabel->setBuddy(host);
    auto portLabel = new QLabel(tr("S&erver port:"));
//    portLabel->setBuddy(portLineEdit);

    auto quitButton = new QPushButton(tr("Quit"));

    auto buttonBox = new QDialogButtonBox;
    buttonBox->addButton(getPictures, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    connect(getPictures, &QAbstractButton::clicked, this, &Client::requestURL);

    connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);

    connect(tcpSocket, &QIODevice::readyRead, this, &Client::read);

    connect(tcpSocket, &QAbstractSocket::errorOccurred, this, &Client::displayError);

    QGridLayout *mainLayout = nullptr;
    if (QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized()) {
        auto outerVerticalLayout = new QVBoxLayout(this);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
        auto outerHorizontalLayout = new QHBoxLayout;
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        auto groupBox = new QGroupBox(QGuiApplication::applicationDisplayName());
        mainLayout = new QGridLayout(groupBox);
        outerHorizontalLayout->addWidget(groupBox);
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        outerVerticalLayout->addLayout(outerHorizontalLayout);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
    } else {
        mainLayout = new QGridLayout(this);
    }
    mainLayout->addWidget(hostLabel, 0, 0);
    mainLayout->addWidget(host, 0, 1);
    mainLayout->addWidget(portLabel, 1, 0);
//    mainLayout->addWidget(portLineEdit, 1, 1);
    mainLayout->addWidget(buttonBox, 3, 0, 1, 2);

    setWindowTitle(QGuiApplication::applicationDisplayName());
}

void Client::requestURL()
{
    getPictures->setEnabled(false);
    tcpSocket->abort();

    tcpSocket->connectToHost(host->text(),45555/*portLineEdit->text().toInt()*/);
}

void Client::read()
{
    in.startTransaction();
    in >> lineOfURLs;
    if (!in.commitTransaction())
        return;
    getPictures->setEnabled(true);

    int i;
    for(i=0;lineOfURLs.indexOf("\n")>=0;i++)
    {
        list.append(lineOfURLs.mid(0, lineOfURLs.toStdString().find("\n")));
        lineOfURLs=lineOfURLs.mid(lineOfURLs.toStdString().find("\n")+1);
    }
    list.append(lineOfURLs);

    qd.resize(list.size());

    for(;!list.isEmpty();)
    {
        qd[i].setTarget(list.takeAt(0));
        qd[i].download_request(i);
        i++;
    }
}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError: break;
    case QAbstractSocket::HostNotFoundError:     QMessageBox::information(this, tr("Fortune Client"), tr("The host was not found. Please check the host name and port settings."));
                                                     break;
    case QAbstractSocket::ConnectionRefusedError:QMessageBox::information(this, tr("Fortune Client"), tr("The connection was refused by the peer. Make sure the fortune server is running, "
                                                     "and check that the host name and port settings are correct."));
                                                     break;
    default:        QMessageBox::information(this, tr("Fortune Client"), tr("The following error occurred: %1.").arg(tcpSocket->errorString()));
    }
    getPictures->setEnabled(true);
}
