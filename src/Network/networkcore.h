#ifndef NETWORKCORE_H
#define NETWORKCORE_H

#include "Abstracts/abstractcore.h"

class FileDownloader;
class QNetworkAccessManager;
class QNetworkDiskCache;

class NetworkCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit NetworkCore(QObject *parent = nullptr);

    void init();

    FileDownloader* createFileDownloader();
private:
    Q_DISABLE_COPY(NetworkCore)

    QNetworkAccessManager* m_manager;
    QNetworkDiskCache* m_cache;
};

#endif // NETWORKCORE_H
