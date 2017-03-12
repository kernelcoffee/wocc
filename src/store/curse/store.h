#ifndef CURSESTORE_H
#define CURSESTORE_H

#include "abstracts/abstractstore.h"

#include <QObject>
#include <QVector>
#include <QDateTime>
#include <QThread>
#include <QMutex>

class NetworkCore;
class FileDownloader;
class AddonDetectJob;

namespace Curse {

class Addon;
class WorldOfWarcraft;

class Store : public AbstractStore
{
    Q_OBJECT
public:
    explicit Store(NetworkCore* network, QObject *parent = nullptr);
    ~Store();

    WorldOfWarcraft* wow();

public slots:
//    AddonDetectJob* detect();

//    bool loadInstalled(bool isAsync = true);
//    bool saveInstalled();


private slots:
    void refresh();
//    void setWowInstalledAddons(const QVector<Addon*> &installedAddons);

private:
    void loadLibraries();

    WorldOfWarcraft* m_wow;

    QVector<Addon*> m_library;

    QDateTime m_lastRefresh;
};

}

#endif // CURSESTORE_H
