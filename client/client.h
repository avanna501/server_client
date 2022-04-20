#ifndef CLIENT_H
#define CLIENT_H

#include <download.h>
#include <QMainWindow>
#include <QDialog>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QVector>
#include <QComboBox>
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>
#include <QHostInfo>
#include <QDataStream>

QT_BEGIN_NAMESPACE
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTcpSocket;
QT_END_NAMESPACE

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    QString lineOfURLs;

private slots:
    void requestURL();
    void read();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    QHostInfo hostIP;
    QLineEdit *host = nullptr;
//    QLineEdit *portLineEdit = nullptr;
    QPushButton *getPictures = nullptr;

    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    QList<QString> list;
    QVector<Downloader> qd;

};

#endif// CLIENT_H
