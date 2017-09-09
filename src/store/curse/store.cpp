#include "store.h"
#include "addon.h"

#include "network/networkcore.h"
#include "network/filedownloader.h"

#include "worldofwarcraft/worldofwarcraft.h"
#include "worldofwarcraft/addondetectjob.h"

#include "xmlparser.h"
#include "downloadfilejob.h"
#include "utilities/fileextractor.h"


#include <QStandardPaths>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QDataStream>
#include <QSettings>

#include <algorithm>

#include <QDebug>

using namespace Curse;

static constexpr char archive_url[] = "http://clientupdate.curse.com/feed/Complete.xml.bz2";

Store::Store(QObject *parent) :
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


AbstractWorker* Store::refresh()
{
    FileDownloader *downloader =  m_network->createFileDownloader();
    downloader->setUrl(archive_url);
    downloader->setFileOverride(true);
    downloader->setDestination(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));

    connect(downloader, &FileDownloader::finished, [this, downloader](){
        QSettings settings;
        settings.beginGroup("Curse");
        settings.setValue("curseArchive", downloader->savedFileLocation());
        settings.endGroup();
        loadLibraries();
        downloader->deleteLater();
    });

    downloader->start();
    return nullptr;
}

void Store::loadLibraries()
{
    QSettings settings;
    XmlParser parser;
    QString xmlOutput = FileExtractor::bzip2FileToString(settings.value("curseArchive").toString());

    QVector<Addon*> library = parser.XmlToAddonList(xmlOutput);
    QVector<Addon*> wowLibrary;
    for (Addon* addon: library) {
        if (addon->gameId() == static_cast<uint>(Games::WorldOfWarcraft)) {
            wowLibrary << addon;
        }
    }

    m_WorldOfWarcraft->setLibrary(wowLibrary);
}
