#ifndef CURSESTORE_H
#define CURSESTORE_H

#include <QObject>
#include <QVector>
#include <QDateTime>
#include <QThread>
#include <QMutex>

class NetworkCore;
class FileDownloader;
class WowAddonDetectionWorker;

namespace Curse {

class Addon;

class Store : public QObject
{
    Q_OBJECT
public:
    explicit Store(NetworkCore* network, QObject *parent = nullptr);
    ~Store();

    QVector<Addon*> wowLibrary() const;

signals:
    void wowLibraryUpdated(const QVector<Addon*> &addonList);
    void wowInstalledListUpdated(const QVector<Addon*> &installedAddonList);

public slots:
    FileDownloader* refresh(bool isAsync = true);
    WowAddonDetectionWorker* detect(bool isAsync = true);
    void update(Addon* addon);
    void install(Addon* addon);
    void remove(Addon* addon);

    void loadLibrary(bool isAsync = true);
    bool loadInstalled(bool isAsync = true);
    bool saveInstalled();

private slots:
    void setWowInstalledAddons(const QVector<Addon*> &installedAddons);

private:
    QVector<Addon*> m_wowLibrary;
    QVector<Addon*> m_wowInstalled;

    QDateTime m_lastRefresh;

    QThread m_workerThread;
    QMutex m_mutex;
    NetworkCore* m_network;
};

}

#endif // CURSESTORE_H
