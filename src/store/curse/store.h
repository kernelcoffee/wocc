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
class AbstractGame;
class AbstractWorker;
class Addon;

namespace Curse {

class WorldOfWarcraft;

class Store : public AbstractStore
{
    Q_PROPERTY(WorldOfWarcraft* worldOfWarcraft READ worldOfWarcraft CONSTANT)

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

    explicit Store(QObject* parent = nullptr);
    ~Store();

    WorldOfWarcraft* worldOfWarcraft();

public slots:
    AbstractWorker* refresh();

private:
    void loadLibraries();

    WorldOfWarcraft* m_WorldOfWarcraft;

    QDateTime m_lastRefresh;
};

}

#endif // STORE_H
