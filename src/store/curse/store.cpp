#include "store.h"
#include "addon.h"

#include "network/networkcore.h"
#include "network/filedownloader.h"
#include "threads/threadcore.h"

#include "worldofwarcraft/worldofwarcraft.h"
#include "worldofwarcraft/detecttask.h"

#include "refreshlibrarytask.h"

#include <QDebug>

using namespace Curse;

Store::Store(QObject* parent) :
    AbstractStore(parent)
    , m_WorldOfWarcraft(new WorldOfWarcraft)
{
    qRegisterMetaType<Addon*>("Addon*");
    qRegisterMetaType<QVector<Curse::Addon*>>("QVector<Curse::Addon*>");
    qRegisterMetaType<QList<Addon::Dependency>>("QList<Addon::Dependency>");
    qRegisterMetaType<QList<Curse::Addon*>>("QList<Curse::Addon*>");
}

Store::~Store()
{
    m_WorldOfWarcraft->deleteLater();
}

void Store::init(NetworkCore* network, ThreadCore* threads)
{
    m_network = network;
    m_threads = threads;

    m_WorldOfWarcraft->init(m_network, m_threads);
}

Curse::WorldOfWarcraft* Store::worldOfWarcraft()
{
    return m_WorldOfWarcraft;
}

QVector<Addon*> Store::getAddonDependencies(Addon* addon)
{
    return addon->dependencyAddons();
}

AbstractTask* Store::refresh()
{
    RefreshLibraryTask* task = new RefreshLibraryTask(m_network->createFileDownloader());
    task->setAutoDelete(true);
    task->setIsUnique(true);

    connect(task, &RefreshLibraryTask::finished, this, &Store::sortLibrary);
    m_threads->addTask(task);
    return task;
}

void Store::sortLibrary(const QVector<Curse::Addon*> library)
{
    QVector<Addon*> wowLibrary;

    qDebug() << "Parsing library";
    for (Addon* addon : library) {
        switch (addon->gameId()) {
        case static_cast<uint>(Games::WORLD_OF_WARCRAFT):
            wowLibrary << addon;
            break;
        default:
            break;
        }
    }

    m_WorldOfWarcraft->setLibrary(wowLibrary);
}
