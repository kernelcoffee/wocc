#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>

class FileDownloader : public QObject
{
    Q_OBJECT
public:
    explicit FileDownloader(QNetworkAccessManager &manager, QObject *parent = 0);
};

#endif // FILEDOWNLOADER_H
