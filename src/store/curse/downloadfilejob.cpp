#include "downloadfilejob.h"

using namespace Curse;

DownloadFileJob::DownloadFileJob(QObject *parent) :
    AbstractJob(parent)
{

}

void DownloadFileJob::run()
{
//    FileDownloader *downloader =  m_network->createFileDownloader();
//    downloader->setUrl(archive_url);
//    downloader->setFileOverride(true);
//    downloader->setDestination(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));

//    connect(downloader, &FileDownloader::finished, [this, downloader](){
//        QSettings settings;
//        settings.setValue("wowCurseArchive", downloader->savedFileLocation());
//        parseLibraries();
//        downloader->deleteLater();
//    });

//    downloader->startSync();

}
