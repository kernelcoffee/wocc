#include "filedownloader.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QSslError>
#include <QFile>
#include <QFileInfo>
#include <QDir>

#include <QEventLoop>

#include <QDebug>

FileDownloader::FileDownloader(QNetworkAccessManager *manager, QObject *parent) :
    QObject(parent)
  , m_manager(manager)
{
    connect(m_manager, &QNetworkAccessManager::finished,
            this, &FileDownloader::onFinished);
}

QUrl FileDownloader::url() const
{
    return m_url;
}

QString FileDownloader::destination() const
{
    return m_destination;
}

uint FileDownloader::progress() const
{
    return m_progress;
}

void FileDownloader::start()
{
    if (m_url.isEmpty()) {
        emit finished();
        return;
    }
    QNetworkRequest request(m_url);
//    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
    m_reply = m_manager->get(request);
//    connect(m_reply, &QNetworkReply::finished, [this](){onFinished(m_reply);});
    connect(m_reply, &QNetworkReply::downloadProgress, [this](qint64 bytesReceived, qint64 bytesTotal) {
        qDebug() << bytesReceived << bytesTotal << 100 * bytesReceived / bytesTotal;
//        setProgress(100 * bytesReceived / bytesTotal);
    });
}

void FileDownloader::startSync()
{
    QEventLoop loop;

    connect(this, &FileDownloader::finished, &loop, &QEventLoop::quit);
    start();

    loop.exec();
}

QString FileDownloader::savedFileLocation() const
{
    return m_saveFileLocation;
}

void FileDownloader::setUrl(const QUrl& url)
{
    if (m_url == url)
        return;

    m_url = url;
    emit urlChanged(url);
}

void FileDownloader::setUrl(const QString& url)
{
    setUrl(QUrl::fromEncoded(url.toLocal8Bit()));
}

void FileDownloader::setDestination(QString destination)
{
    if (m_destination == destination) {
        return;
    }

    m_destination = destination;
    emit destinationChanged(destination);
}

void FileDownloader::setProgress(uint progress)
{
    if (m_progress == progress) {
        return;
    }

    m_progress = progress;
    emit progressChanged(progress);
}

void FileDownloader::setSavedFileLocation(const QString& savedFileLocation)
{
    if (m_saveFileLocation == savedFileLocation) {
        return;
    }

    m_saveFileLocation = savedFileLocation;
    emit savedFileLocationChanged(savedFileLocation);
}

void FileDownloader::setFileOverride(bool override)
{
    m_overrideSavedFile = override;
}

void FileDownloader::onFinished(QNetworkReply *reply)
{
    if (!reply) {
        qDebug() << "reply is null";
        return;
    }
    qDebug() << "Cache used : " << reply->attribute(QNetworkRequest::SourceIsFromCacheAttribute).toBool();
    QUrl url = reply->url();
    if (reply->error()) {
        qWarning() << QString("Download of %1 failed: %2").arg(url.toEncoded(), reply->errorString());
        return;
    }
    QString filePath = m_destination + QDir::separator() + saveFileName(url);

    if (!saveToDisk(filePath, reply)) {
        qWarning() << "Saving to disk failed" <<  filePath;
        return;
    }

    qInfo() << QString("Download of %1 succeded (saved to %2)").arg(url.toEncoded(), filePath);


    reply->deleteLater();
    setSavedFileLocation(filePath);
    emit finished();
}

QString FileDownloader::saveFileName(const QUrl& url)
{
    QString basename = QFileInfo(url.path()).fileName();

    if (basename.isEmpty()) {
        basename = "download";
    }

    if (QFile::exists(basename) && !m_overrideSavedFile) {
        // already exists, don't overwrite
        int i = 0;
        basename += '.';
        while (QFile::exists(basename + QString::number(i)))
            ++i;

        basename += QString::number(i);
    }

    return basename;
}

bool FileDownloader::saveToDisk(const QString& filePath, QIODevice* data)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << QString("Could not open %1 for writing: %2").arg(filePath, file.errorString());
        return false;
    }

    file.write(data->readAll());
    file.close();

    return true;
}
