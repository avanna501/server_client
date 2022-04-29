#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QString>
#include <QTcpServer>

class MyServer : public QTcpServer
{
    Q_OBJECT

public:
    MyServer();

private:
    QString list;

private slots:
    void incoming_connection();
    void read_tosend();
};
#endif // SERVER_H
