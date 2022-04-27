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

    QFile file_del(QString("C:/Users/inter/projects_a/client_server/server_client/download/downloaded_file_%1.png").arg(i));
    file_del.remove();
}
Downloader::Downloader(const Downloader &){};

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
        return;
    file_name=QString("C:/Users/inter/projects_a/client_server/server_client/download/downloaded_file_%1.png").arg(i);
    QFile localFile(file_name);/*localFile.setFileName*/
    if (!localFile.open(QIODevice::WriteOnly))
        return ;
    auto data = rep->readAll();
    if (rep->error() != QNetworkReply::NoError)
    {
        qInfo()<<"error in download _" << target << i << "_" << rep->error();
        return;
    }
    localFile.write(data);

    localFile.flush();
    localFile.close();
    qInfo()<<"download_"<<i;
    if (i==0)

        emit done_0();

//    rep->deleteLater();
}
