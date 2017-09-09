#ifndef STORE_H
#define STORE_H

#include "abstracts/abstractstore.h"

class NetworkCore;
class FileDownloader;
class AddonDetectTask;
class AbstractGame;
class AbstractTask;
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
    AbstractTask* refresh();
    void loadLibraries();

private:
    WorldOfWarcraft* m_WorldOfWarcraft;
};

}

#endif // STORE_H
