#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

class Downloader : public QObject
{
    Q_OBJECT

public:
    explicit Downloader();
    ~Downloader();
    Downloader(const Downloader&);

    void setTarget(const QString& t);
    void download_request(int j);
    void download();
    Downloader& operator=(const Downloader& other) {target = other.target; return *this; }

//    QFile localFile;

private:
    QNetworkAccessManager manager;
    QString target;
    int i;
    QString file_name;

//public slots:

};

#endif // DOWNLOAD_H
