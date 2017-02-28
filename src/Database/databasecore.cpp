#include "databasecore.h"
#include "coremanager.h"
#include "Network/filedownloader.h"
#include "wowcursexmlparser.h"

#include <QStandardPaths>
#include <QProcess>
#include <QXmlStreamReader>

#include <QDebug>


static constexpr char database_url[] = "http://clientupdate.curse.com/feed/Complete.xml.bz2";

DatabaseCore::DatabaseCore(CoreManager *parent) :
    AbstractCore(parent)
  , m_network(parent->network())
{
}

DatabaseCore::~DatabaseCore()
{
    qDeleteAll(m_database);
}

QVector<WowAddon*> DatabaseCore::addonList() const
{
    return addonList();
}

void DatabaseCore::update(bool isAsync)
{
    qDebug() << m_network;
    FileDownloader *downloader =  m_network->createFileDownloader();
    downloader->setUrl(database_url);
    downloader->setFileOverride(true);
    downloader->setDestination(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));

    connect(downloader, &FileDownloader::finished, [this, downloader](){
            decompressBzip2File(downloader->savedFileLocation());
            downloader->deleteLater();
            emit wowAddonListUpdated(m_database);
    });

    if (isAsync) {
        downloader->start();
    } else {
        downloader->startSync();
    }
}

bool DatabaseCore::decompressBzip2File(const QString filePath)
{
    QProcess process(this);
    process.start("bzip2", {"-dkc", filePath});
    if (!process.waitForStarted()) {
        return false;
    }

    if (!process.waitForFinished()) {
        return false;
    }

    qDebug() << filePath << "decompressed";
    WowCurseXmlParser parser;
    m_database = parser.XmlToAddonList(process.readAll());
    return true;
}
