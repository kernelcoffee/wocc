#include "cursestore.h"
#include "Network/networkcore.h"
#include "Network/filedownloader.h"
#include "Utilities/fileextractor.h"
#include "wowcursexmlparser.h"
#include "wowaddon.h"

#include <QStandardPaths>
#include <QXmlStreamReader>
#include <QUrl>
#include <QDir>
#include <QSettings>
#include <QSet>

#include <algorithm>

#include <QDebug>

static constexpr char archive_url[] = "http://clientupdate.curse.com/feed/Complete.xml.bz2";

CurseStore::CurseStore(NetworkCore* network, QObject *parent) :
    QObject(parent)
  , m_network(network)
{

}

CurseStore::~CurseStore()
{
    qDeleteAll(m_wowLibrary);
}

void CurseStore::refresh(bool isAsync)
{
    FileDownloader *downloader =  m_network->createFileDownloader();
    downloader->setUrl(archive_url);
    downloader->setFileOverride(true);
    downloader->setDestination(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));

    connect(downloader, &FileDownloader::finished, [this, downloader](){
        QSettings settings;
        settings.setValue("wowCurseArchive", downloader->savedFileLocation());
        processWowArchive();
    });

    if (isAsync) {
        downloader->start();
    } else {
        downloader->startSync();
    }
}

// Not really optimized but it works.
void CurseStore::detect()
{
    QSettings settings;

    QDir dir(QUrl(settings.value("wowDir").toString()).toLocalFile() + "/Interface/AddOns");

    qDebug() << dir.absolutePath();
    if (!dir.exists()) {
        qDebug() << "path doesn't exist";
    }

    QStringList entries = dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs);

    QMap<QString, QSet<QString>> tmpMap;

    // Let's create a map of addons per folder installed
    for (auto entry : entries) {
        for (auto addon : m_wowLibrary) {
            for (auto file : addon->files()) {
                for (auto module : file.modules) {
                    if (module.folderName.startsWith(entry, Qt::CaseInsensitive)) {
                        if (!tmpMap[entry].contains(addon->shortName())) {
                            tmpMap[entry] << addon->shortName();
                        }
                    }
                }
            }
        }
    }

    QSet<QString> possibleAddons;
    // Create a list of possible addon installed
    for (auto addonset : tmpMap) {
        for (auto addon : addonset) {
            if (!possibleAddons.contains(addon)) {
                possibleAddons << addon;
            }
        }
    }

    qDebug() << "Premiminary addon detection :" << possibleAddons.count();

    // We'll detect addon by matching the folders to what they contains.
    QVector<WowAddon*> badAddons;
    m_wowInstalled.clear();

    for (const QString &possibleAddon : possibleAddons) {

        // let's retrieve the AddOn using the shortname
        auto itObj = std::find_if(m_wowLibrary.begin(), m_wowLibrary.end(),
                                  [=](WowAddon* addon){
            return addon->shortName() == possibleAddon;
        });

        if (itObj == m_wowLibrary.constEnd()) {
            continue;
        }

        WowAddon* addon = (*itObj);
        int addonFolderDetected = 0;
        bool matches = false;

        // addons can have multiple versions (when dependencies are added for ex.)
        for (auto file : addon->files()) {
            // each file is composed of modules
            addonFolderDetected = 0;
            for (auto module : file.modules) {
                // we match the number of files detected with the number of file registered
                for (auto installedFolder : entries) {
                    if (module.folderName == installedFolder) {
                        addonFolderDetected++;
                    }
                }
            }

            // We check if the number of folder match with the database
            if (addonFolderDetected == file.modules.count()) {
                //qDebug() << "Add matched perfectly" << addon->name();
                matches = true;
            }
        }

        if (matches) {
            m_wowInstalled << addon;
        } else {
            badAddons << addon;
        }
    }
    qDebug() << "Addon detected" << m_wowInstalled.count();
    qDebug() << "addon rejected" << badAddons.count();
    emit wowInstalledListUpdated(m_wowInstalled);

}

void CurseStore::processWowArchive()
{
    QSettings settings;
    WowCurseXmlParser parser;
    QString xmlOutput = FileExtractor::bzip2FileToString(settings.value("wowCurseArchive").toString());
    m_wowLibrary = parser.XmlToAddonList(xmlOutput);

    emit wowLibraryUpdated(m_wowLibrary);
}
