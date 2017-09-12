#include "installtask.h"
#include "store/curse/addon.h"
#include "network/filedownloader.h"

#include <QDebug>

using namespace Curse;

InstallTask::InstallTask(Addon* addon, FileDownloader* downloader, QObject* parent) :
    AbstractTask(parent)
    , m_addon(addon)
    , m_downloader(downloader)
{

}

void InstallTask::start()
{
    setStatus(Running);

    qDebug() << m_addon->shortName() << m_addon->versionAvailable();
    for (auto file : m_addon->files()) {
        qDebug() << file.name << file.downloadUrl;
        for (auto module : file.modules) {
            qDebug() << '\t' << module.folderName << module.fingerprint;
        }
    }

    //    downloader->setUrl(addon->files().first().downloadUrl);
    //    downloader->setFileOverride(true);
    //    downloader->setDestination(QStandardPaths::writableLocation(QStandardPaths::TempLocation));

    //    connect(downloader, &FileDownloader::finished, [this, downloader]() {
    //        QSettings settings;
    //        QString dest = QUrl(settings.value("wowDir").toString() + "/Interface/AddOns").toLocalFile();
    //        FileExtractor::unzip(downloader->savedFileLocation(), dest);
    //        downloader->deleteLater();
    //        detect();
    //    });

    setStatus(Success);
}

void InstallTask::cancel()
{
    qDebug() << "Cancelling task";
}

