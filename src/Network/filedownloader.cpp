#include "filedownloader.h"

#include <QNetworkAccessManager>

FileDownloader::FileDownloader(QNetworkAccessManager &manager, QObject *parent) :
    QObject(parent)
{
    Q_UNUSED(manager)
}
