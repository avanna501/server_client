#include "downloader.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include <QPixmap>
#include <QString>

Downloader::Downloader() : QObject(0)
{}
Downloader::~Downloader(){}

void Downloader::setTarget(const QString &t)
{
    this->target = t;
}

void Downloader::download_request()
{
    QUrl url = target;
    QNetworkRequest request(url);
    QNetworkReply* reply = manager.get(request);

    QObject::connect(reply,&QNetworkReply::finished,this,&Downloader::download);
}

void Downloader::download()
{
    auto rep = dynamic_cast<QNetworkReply*>(sender());
    if(!rep){
        return;
    }
    file_name=QStringLiteral("C:/Users/inter/projects_a/client_server/server_client/download/downloadedfile1_%1.png").arg(i);
    QFile localFile(file_name);
    if (!localFile.open(QIODevice::WriteOnly))
        return ;
    auto data = rep->readAll();
    localFile.write(data);
    localFile.close();
}
