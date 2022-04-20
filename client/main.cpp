#include "client.h"
#include "download.h"
#include <QString>
#include <QList>
#include <QCoreApplication>
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    client.show();
    return a.exec();
}
