#include "networkcore.h"
#include "filedownloader.h"

#include <QNetworkAccessManager>
#include <QNetworkDiskCache>
#include <QStandardPaths>

#include <QDebug>

NetworkCore::NetworkCore(QObject* parent) :
    AbstractCore(parent)
    , m_manager(new QNetworkAccessManager)
    , m_cache(new QNetworkDiskCache)
{
}

void NetworkCore::init()
{
    m_cache->setCacheDirectory(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    m_manager->setCache(m_cache);
}

void NetworkCore::print()
{
    qDebug() << "Network Info";
    qDebug() << "SSL version" << QSslSocket::sslLibraryVersionString();
    qDebug() << "SSL build Version" << QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "SSL supported" << QSslSocket::supportsSsl();
}

FileDownloader* NetworkCore::createFileDownloader()
{
    return new FileDownloader(m_manager, this);;
}
