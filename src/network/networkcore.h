#ifndef NETWORKCORE_H
#define NETWORKCORE_H

#include "abstracts/abstractcore.h"

class FileDownloader;
class QNetworkAccessManager;
class QNetworkDiskCache;

class NetworkCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit NetworkCore(QObject* parent = nullptr);

    virtual void init() override;
    virtual void print() override;

    FileDownloader* createFileDownloader();
private:
    Q_DISABLE_COPY(NetworkCore)

    QNetworkAccessManager* m_manager;
    QNetworkDiskCache* m_cache;
};

#endif // NETWORKCORE_H
