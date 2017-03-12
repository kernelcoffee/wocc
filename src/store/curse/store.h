#ifndef STORE_H
#define STORE_H

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
    enum class Games {
        WorldOfWarcraft = 1,
        TheSecretWorld = 64,
        RuneOfMagic = 335,
        WorldOfTank = 423,
        Ryft = 424,
        MineCraft = 432,
        Skyrim = 449,
        WildStar = 454,
        TheElderScrollOnline = 455,
        Firefall = 456
    };

    explicit Store(NetworkCore* network, QObject *parent = nullptr);
    ~Store();

    WorldOfWarcraft* wow();

//public slots:
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

#endif // STORE_H
