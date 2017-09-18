#include "installtask.h"
#include "store/curse/addon.h"
#include "network/filedownloader.h"
#include "utilities/fileextractor.h"

#include <QDebug>
#include <QStandardPaths>
#include <QSettings>
#include <QDir>

using namespace Curse;

InstallTask::InstallTask(Addon* addon, FileDownloader* downloader, QObject* parent) :
    AbstractTask(parent)
    , m_addon(addon)
    , m_downloader(downloader)
{
    m_name = tr("Install Addon %1").arg(addon->name());

    QSettings settings;
    settings.beginGroup("WorldOfWarcraft");
    m_dest = QUrl(settings.value("location").toString() + "/Interface/AddOns/");
    settings.endGroup();


    m_downloader->setUrl(addon->files().first().downloadUrl);
    m_downloader->setFileOverride(true);
    m_downloader->setDestination(QStandardPaths::writableLocation(QStandardPaths::TempLocation));
    connect(m_downloader, &FileDownloader::finished, this, &InstallTask::onDownloadFinished);
}

InstallTask::~InstallTask()
{
    m_downloader->deleteLater();
}

void InstallTask::start()
{
    setStatus(Running);
    m_downloader->start();
}

void InstallTask::cancel()
{
    qDebug() << "Cancelling task";
}

void InstallTask::onDownloadFinished()
{
    qDebug() << "File downloaded, now installing";


    const QString& file = m_downloader->savedFileLocation();
    const QDir& dest(m_dest.toLocalFile());

    qDebug() << dest.absolutePath();
    return;

    FileExtractor::unzip(file, dest.absolutePath());
    m_addon->setIsInstalled(true);

    emit finished();
    setStatus(Success);
}

