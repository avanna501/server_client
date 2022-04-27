#ifndef CLIENT_H
#define CLIENT_H

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

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    QString lineOfURLs;

private slots:
    void requestURL();
    void read();
    void displayError(QAbstractSocket::SocketError socketError);

public:
    QHostInfo hostIP;
    QLineEdit *host = nullptr;
    QPushButton *getPictures = nullptr;

    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    QString line;

};


//class C : public QObject
//{
//    Q_OBJECT
//    int counter=0;
//    bool h;

//    public:
//        QPushButton * p;
//        QCheckBox * box;
//        string * t;

//    public slots:
//        void setValue(bool click)
//        {
//            counter++;
//            if (box->isChecked())
//                p->setText(QString("the counter is %1").arg(counter));
//            else
//                p->setText("The box is not checked");
//        }
//};

//#endif // HEADER_H

#endif// CLIENT_H
