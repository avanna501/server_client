#include "server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationDisplayName(MyServer::tr("Server"));
    MyServer server;
    return app.exec();
}
