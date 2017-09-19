#ifndef STORE_H
#define STORE_H

#include "abstracts/abstractstore.h"
#include "addon.h"

#include <QHash>

class NetworkCore;
class ThreadCore;

class FileDownloader;
class DetectTask;
class AbstractGame;
class AbstractTask;

namespace Curse {

class WorldOfWarcraft;

class Store : public AbstractStore
{
    Q_PROPERTY(WorldOfWarcraft* worldOfWarcraft READ worldOfWarcraft CONSTANT)

    Q_OBJECT
public:
    enum class Games {
        WORLD_OF_WARCRAFT = 1,
        THE_SECRET_WORLD = 64,
        RUNE_OF_MAGIC = 335,
        WORLD_OF_TANK = 423,
        RYFT = 424,
        MINECRAFT = 432,
        SKYRIM = 449,
        WILD_STAR = 454,
        THE_ELDER_SCROLL_ONLINE = 455,
        FIREBALL = 456
    };
    Q_ENUM(Games)

    explicit Store(QObject* parent = nullptr);
    ~Store();

    void init(NetworkCore* network, ThreadCore* threads);
    WorldOfWarcraft* worldOfWarcraft();

    QVector<Curse::Addon::Dependency> getAddonDependencies(Addon* addon);

public slots:
    AbstractTask* refresh();

private slots:
    void sortLibrary(const QVector<Curse::Addon*> library);

private:
    NetworkCore* m_network;
    ThreadCore* m_threads;

    WorldOfWarcraft* m_WorldOfWarcraft;
};
}
Q_DECLARE_METATYPE(Curse::Store::Games)

#endif // STORE_H
