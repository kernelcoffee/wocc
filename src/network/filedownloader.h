#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include "abstracts/abstracttask.h"
#include <QObject>
#include <QUrl>
#include <QString>

class QNetworkAccessManager;
class QNetworkReply;
class QIODevice;

class FileDownloader : public AbstractTask
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString destination READ destination WRITE setDestination NOTIFY destinationChanged)
public:
    explicit FileDownloader(QNetworkAccessManager* manager, QObject* parent = nullptr);

    QUrl url() const;
    QString destination() const;
    QString savedFileLocation() const;

    void start();
    void startSync();

signals:
    void urlChanged(const QUrl& url);
    void destinationChanged(const QString& destination);
    void savedFileLocationChanged(const QString& savedFileLocation);

public slots:
    void setUrl(const QUrl& url);
    void setUrl(const QString& url);
    void setDestination(QString destination);
    void setSavedFileLocation(const QString& savedFileLocation);
    void setFileOverride(bool override);

private slots:
    void onFinished(QNetworkReply* reply);

private:
    QString saveFileName(const QUrl& url);
    bool saveToDisk(const QString& filePath, QIODevice* data);

    QNetworkAccessManager* m_manager;
    QNetworkReply* m_reply;
    QUrl m_url;
    QString m_destination;
    QString m_saveFileLocation;
    bool m_overrideSavedFile;
};

#endif // FILEDOWNLOADER_H
