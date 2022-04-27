#include "download.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include <QPixmap>
#include <QString>

Downloader::Downloader() : QObject(0)
{
    qInfo()<<"created";
}
Downloader::~Downloader()
{

    qInfo()<<"destroyed "<<i;
    if(i>=0)
    {
        QFile file_del(file_name);
        file_del.remove();
    }
}
Downloader::Downloader(const Downloader &d){i=d.i;};

void Downloader::setTarget(const QString &t)
{
    this->target = t;
}

void Downloader::download_request(int j)
{
    QUrl url = target;
    QNetworkRequest request(url);
    QNetworkReply* reply = manager.get(request);
    i=j;
    QObject::connect(reply,&QNetworkReply::finished,this,&Downloader::download);
}

void Downloader::download()
{
    auto rep = dynamic_cast<QNetworkReply*>(sender());
    if(!rep)
    {
        i=-1;
        return;
    }
    file_name=QString("downloaded_file_%1.png").arg(i);
    QFile localFile(file_name);
    if (!localFile.open(QIODevice::WriteOnly))
    {
        i=-1;
        return;
    }
    auto data = rep->readAll();
    if (rep->error() != QNetworkReply::NoError)
    {
        qInfo()<< i << "_" << rep->error();
        return;
    }
    localFile.write(data);
    localFile.flush();
    localFile.close();
    qInfo()<<"download "<<i;
    if (i==0)
        emit done_0();
}
