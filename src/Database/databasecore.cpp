#include "databasecore.h"
#include "coremanager.h"
#include "Network/filedownloader.h"


#include <QStandardPaths>

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
    downloader->setDestination(QStandardPaths::displayName(QStandardPaths::CacheLocation));

    if (isAsync) {
        downloader->start();
    } else {
        downloader->startSync();
    }
}
