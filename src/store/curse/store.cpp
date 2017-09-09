#include "store.h"
#include "addon.h"

#include "network/networkcore.h"
#include "network/filedownloader.h"

#include "worldofwarcraft/worldofwarcraft.h"
#include "worldofwarcraft/addondetecttask.h"

#include "xmlparser.h"
#include "downloadfilejob.h"
#include "utilities/fileextractor.h"
#include "refreshlibrarytask.h"


#include <QStandardPaths>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QDataStream>

#include <QSettings>
#include <QDebug>

using namespace Curse;

Store::Store(QObject* parent) :
    AbstractStore(parent)
    , m_WorldOfWarcraft(new WorldOfWarcraft)
{
}

Store::~Store()
{
    m_WorldOfWarcraft->deleteLater();
}

Curse::WorldOfWarcraft* Store::worldOfWarcraft()
{
    return m_WorldOfWarcraft;
}

AbstractTask* Store::refresh()
{
    RefreshLibraryTask* task = new RefreshLibraryTask(m_network->createFileDownloader());
    task->setAutoDelete(true);
    task->setIsUnique(true);

    connect(task, &RefreshLibraryTask::finished, this, &Store::loadLibraries);

    task->start();

    return task;
}

void Store::loadLibraries()
{
    QSettings settings;
    XmlParser parser;
    QString xmlOutput = FileExtractor::bzip2FileToString(settings.value("curseArchive").toString());

    QVector<Addon*> library = parser.XmlToAddonList(xmlOutput);
    QVector<Addon*> wowLibrary;
    for (Addon* addon : library) {
        switch (addon->gameId()) {
        case static_cast<uint>(Games::WorldOfWarcraft):
            wowLibrary << addon;
            break;
        default:
            break;
        }
    }

    m_WorldOfWarcraft->setLibrary(wowLibrary);
}
