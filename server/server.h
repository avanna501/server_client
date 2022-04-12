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

public slots:
    void incoming_connection();

private:
    QTcpSocket * soc;
    QVector<QTcpSocket*> s;
    QString file_name="C:/Users/inter/projects_a/fortune_example/my_fortune/list_of_fortunes.txt";
    QList<QString> list={};
};
//qintptr socketDescriptor
#endif // SERVER_H
