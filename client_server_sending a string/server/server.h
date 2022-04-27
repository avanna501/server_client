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
    void read();
    void show();
    QString file_name="C:/Users/inter/projects_a/client_server/server_client/client_server_sending a string/server/text.txt";

public slots:
    void incoming_connection();
private:
    QTcpSocket * soc;
    QVector<QTcpSocket*> s;
    QString list;
};
#endif // SERVER_H
