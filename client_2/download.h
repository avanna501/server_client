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
    Downloader& operator=(const Downloader& other) {target = other.target; return *this; }

    void setTarget(const QString& t);
    void download_request(int j);
    QString file_name;

private:
    QNetworkAccessManager manager;
    QString target;
    int i=-1;
    void download();

signals:
    void done_0();

};
#endif // DOWNLOAD_H
