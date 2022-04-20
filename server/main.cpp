#include "server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationDisplayName(MyServer::tr("Server"));
    MyServer server;
//    server.show();
    return app.exec();
}
