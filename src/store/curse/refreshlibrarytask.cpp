#include "refreshlibrarytask.h"
#include "network/networkcore.h"
#include "network/filedownloader.h"
#include "store/curse/addon.h"

#include "xmlparser.h"
#include "utilities/fileextractor.h"

#include <QSettings>
#include <QStandardPaths>
#include <QMutexLocker>

#include <QDebug>

static constexpr char ARCHIVE_URL[] = "http://clientupdate.curse.com/feed/Complete.xml.bz2";

using namespace Curse;

RefreshLibraryTask::RefreshLibraryTask(FileDownloader* downloader, QObject* parent) :
    AbstractTask(parent)
    , m_downloader(downloader)
{
    m_name = tr("Refresh Library");
    m_downloader->setUrl(ARCHIVE_URL);
    m_downloader->setFileOverride(true);
    m_downloader->setDestination(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    connect(m_downloader, &FileDownloader::finished, this, &RefreshLibraryTask::onDownloadFinished);
}

RefreshLibraryTask::~RefreshLibraryTask()
{
    m_downloader->deleteLater();
}

void RefreshLibraryTask::start()
{
    QMutexLocker lock(&m_mutex);
    setStatus(Running);
    m_downloader->start();
}

void RefreshLibraryTask::cancel()
{
    qDebug() << "cancelling refresh library";
    if (m_downloader != nullptr) {
        m_downloader->cancel();
    }
}

void RefreshLibraryTask::onDownloadFinished()
{
    qDebug() << "File Downloaded";

    QMutexLocker lock(&m_mutex);

    QSettings settings;
    settings.beginGroup("Curse");
    settings.setValue("curseArchive", m_downloader->savedFileLocation());
    settings.endGroup();
    XmlParser parser;

    QString xmlOutput = FileExtractor::bzip2FileToString(settings.value("curseArchive").toString());
    QVector<Curse::Addon*> library = parser.XmlToAddonList(xmlOutput);

    emit finished(library);
    delete m_downloader;
    m_downloader = nullptr;
    setStatus(Success);
}
