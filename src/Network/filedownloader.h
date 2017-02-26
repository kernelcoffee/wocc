#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>

class FileDownloader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString destination READ destination WRITE setDestination NOTIFY destinationChanged)
    Q_PROPERTY(uint progress READ progress WRITE setProgress NOTIFY progressChanged)
public:
    explicit FileDownloader(QNetworkAccessManager *manager, QObject *parent = nullptr);

    QUrl url() const;
    QString destination() const;
    uint progress() const;

    void start();
    void startSync();

public slots:
    void setUrl(const QUrl &url);
    void setUrl(const QString &url);
    void setDestination(QString destination);
    void setProgress(uint progress);
    void downloadFinished(QNetworkReply *reply);

signals:
    void urlChanged(const QUrl &url);
    void destinationChanged(QString destination);
    void progressChanged(uint progress);
    void finished();

private:
    QString saveFileName(const QUrl &url);
    bool saveToDisk(const QString &filename, QIODevice *data);

    QNetworkAccessManager* m_manager;
    QNetworkReply* m_reply;
    QUrl m_url;
    QString m_destination;
    uint m_progress;
};

#endif // FILEDOWNLOADER_H
