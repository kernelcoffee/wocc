#include "databasecore.h"
#include "coremanager.h"
#include "Network/filedownloader.h"


#include <QStandardPaths>
#include <QProcess>

static constexpr char database_url[] = "http://clientupdate.curse.com/feed/Complete.xml.bz2";

DatabaseCore::DatabaseCore(CoreManager *parent) :
    AbstractCore(parent)
  , m_network(parent->network())
{

}

void DatabaseCore::update(bool isAsync)
{
    FileDownloader *downloader =  m_network->createFileDownloader();
    downloader->setUrl(database_url);
    downloader->setFileOverride(true);
    downloader->setDestination(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));

    if (isAsync) {
        downloader->start();
    } else {
        downloader->startSync();
    }

    inflate(downloader->savedFileLocation());

}

bool DatabaseCore::inflate(const QString filePath)
{
    QProcess process(this);
    process.start("bzip2", {"-dk", filePath});
    if (!process.waitForStarted()) {
        return false;
    }

    if (!process.waitForFinished()) {
        return false;
    }

    qDebug() << process.readAll();
    return true;
}
