#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QFile>
#include <QRandomGenerator>
#include <QTcpServer>
#include <QTcpSocket>

class MyServer : public QTcpServer
{
    Q_OBJECT

public:
    MyServer();
    void read_tosend();
    QString file_name="list.txt";

public slots:
    void incoming_connection();
private:
    QTcpSocket * soc;
    QVector<QTcpSocket*> s;
    QString list;
};
#endif // SERVER_H
