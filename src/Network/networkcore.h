#ifndef NETWORKCORE_H
#define NETWORKCORE_H

#include "Abstracts/abstractcore.h"
#include <QNetworkAccessManager>

class FileDownloader;

class NetworkCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit NetworkCore(QObject *parent = nullptr);

    FileDownloader* createFileDownloader();
private:
    Q_DISABLE_COPY(NetworkCore)

    QNetworkAccessManager m_manager;
};

#endif // NETWORKCORE_H
