#include "filedownloader.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QSslError>
#include <QFile>
#include <QFileInfo>
#include <QUrl>

#include <QEventLoop>

#include <QDebug>

FileDownloader::FileDownloader(QNetworkAccessManager *manager, QObject *parent) :
    QObject(parent)
  , m_manager(manager)
{
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(downloadFinished(QNetworkReply*)));
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
        qDebug() << "not url set";
        emit downloadFinished(nullptr);
        return;
    }
    QNetworkRequest request(m_url);
    m_reply = m_manager->get(request);
    connect(m_reply, &QNetworkReply::downloadProgress, [this](qint64 bytesReceived, qint64 bytesTotal) {
        qDebug() << bytesReceived << bytesTotal;
    });

    qDebug() << "QDebug started";
}

void FileDownloader::startSync()
{
    QEventLoop loop;

    connect(this, &FileDownloader::finished, &loop, &QEventLoop::quit);
    start();

    loop.exec();
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
    if (m_destination == destination)
        return;

    m_destination = destination;
    emit destinationChanged(destination);
}

void FileDownloader::setProgress(uint progress)
{
    if (m_progress == progress)
        return;

    m_progress = progress;
    emit progressChanged(progress);
}

void FileDownloader::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if (reply->error()) {
        qWarning() << QString("Download of %1 failed: %2").arg(url.toEncoded(), reply->errorString());
    } else {
        QString filename = saveFileName(url);
        if (saveToDisk(filename, reply))
            qInfo() << QString("Download of %1 succeded (saved to %2)").arg(url.toEncoded(), filename);
    }

    reply->deleteLater();
    emit finished();
}

QString FileDownloader::saveFileName(const QUrl& url)
{
    QString basename = QFileInfo(url.path()).fileName();

    qDebug() << basename;

    if (basename.isEmpty()) {
        basename = "download";
    }

    if (QFile::exists(basename)) {
        // already exists, don't overwrite
        int i = 0;
        basename += '.';
        while (QFile::exists(basename + QString::number(i)))
            ++i;

        basename += QString::number(i);
    }

    return basename;
}

bool FileDownloader::saveToDisk(const QString& filename, QIODevice* data)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << QString("Could not open %1 for writing: %2").arg(filename, file.errorString());
        return false;
    }

    file.write(data->readAll());
    file.close();

    return true;
}
