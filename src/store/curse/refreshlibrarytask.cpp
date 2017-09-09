#include "refreshlibrarytask.h"
#include "network/networkcore.h"
#include "network/filedownloader.h"

#include <QSettings>
#include <QStandardPaths>
#include <QMutexLocker>

static constexpr char ARCHIVE_URL[] = "http://clientupdate.curse.com/feed/Complete.xml.bz2";

RefreshLibraryTask::RefreshLibraryTask(FileDownloader* downloader, QObject* parent) :
    AbstractTask(parent)
    , m_downloader(downloader)
{
    m_name = tr("Refresh Library");
    m_downloader->setUrl(ARCHIVE_URL);
    m_downloader->setFileOverride(true);
    m_downloader->setDestination(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    connect(m_downloader, &FileDownloader::finished, this, &RefreshLibraryTask::onFinished);
}

RefreshLibraryTask::~RefreshLibraryTask()
{
    m_downloader->deleteLater();
}

void RefreshLibraryTask::start()
{
    QMutexLocker lock(&m_mutex);
    m_downloader->start();
}

void RefreshLibraryTask::onFinished()
{
    QMutexLocker lock(&m_mutex);
    QSettings settings;
    settings.beginGroup("Curse");
    settings.setValue("curseArchive", m_downloader->savedFileLocation());
    settings.endGroup();
    emit finished();
    if (m_autoDelete) {
        deleteLater();
    }
}
