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

    setIsUnique(true);
    setAutoDelete(true);

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
    setStatus(Canceled);
    qDebug() << "cancelling refresh library";
    if (m_downloader != nullptr) {
        m_downloader->cancel();
    }
    emit cancelled();
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
    m_library = parser.XmlToAddonList(xmlOutput);

    for (auto addon : m_library) {
        linkDependencies(addon);
    }

    emit finished(m_library);
    setStatus(Success);
}

void RefreshLibraryTask::linkDependencies(Addon* addon)
{
    if (addon->dependencies().count() <= 0 || !addon->dependencyAddons().isEmpty()) {
        return;
    }

    qDebug() << "Getting " << addon->dependencies().count() << " dependencies for " <<
             addon->shortName();

    QVector<Addon*> dependencies;

    for (auto dep : addon->dependencies()) {
        if (m_cache.contains(dep.id)) {
            qDebug() << "From cache " << m_cache[dep.id]->shortName() << " from " << addon->shortName();
            dependencies << m_cache[dep.id];
        } else {
            for (Addon* lAddon : m_library) {
                if (dep.id == lAddon->id()) {
                    qDebug() << "new dependency" << lAddon->shortName() << " from " << addon->shortName();
                    m_cache[dep.id] = lAddon;
                    dependencies << lAddon;
                    linkDependencies(lAddon);
                    continue;
                }
            }
        }
    }

    addon->setDependencyAddons(dependencies);
}
