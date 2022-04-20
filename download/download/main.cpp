#include "downloader.h"
#include <QTimer>
#include <QApplication>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    Downloader dl;
    dl.setTarget("https://full.am/uploads/posting_image/user_33976/product_155838/94675a6110296afccce445a3b957b77d.jpg");
    dl.download_request();
    return app.exec();
}
