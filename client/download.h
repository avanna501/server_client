#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Downloader : public QObject
{
    Q_OBJECT

public:
    explicit Downloader();
    ~Downloader();
    Downloader(const Downloader&);

    void setTarget(const QString& t);

private:
    QNetworkAccessManager manager;
    QString target;
    int i;
    QString file_name;

public slots:
    void download_request(int j);
    void download();
};


#endif // DOWNLOADER_H
