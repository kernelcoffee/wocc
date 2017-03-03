#ifndef CURSESTORE_H
#define CURSESTORE_H

#include <QObject>
#include <QVector>
#include <QDateTime>
#include <QThread>
#include <QMutex>

class WowAddon;
class NetworkCore;
class FileDownloader;
class WowAddonDetectionWorker;

class CurseStore : public QObject
{
    Q_OBJECT
public:
    explicit CurseStore(NetworkCore* network, QObject *parent = nullptr);
    ~CurseStore();

    QVector<WowAddon*> wowLibrary() const;

signals:
    void wowLibraryUpdated(const QVector<WowAddon*> &addonList);
    void wowInstalledListUpdated(const QVector<WowAddon*> &installedAddonList);

public slots:
    FileDownloader* refresh(bool isAsync = true);
    WowAddonDetectionWorker* detect(bool isAsync = true);

    void loadLibrary(bool isAsync = true);
    bool loadInstalled(bool isAsync = true);
    bool saveInstalled();

private slots:
    void setWowInstalledAddons(const QVector<WowAddon*> &installedAddons);

private:
    QVector<WowAddon*> m_wowLibrary;
    QVector<WowAddon*> m_wowInstalled;

    QDateTime m_lastRefresh;

    QThread m_workerThread;
    QMutex m_mutex;
    NetworkCore* m_network;
};

#endif // CURSESTORE_H
