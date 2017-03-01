#include "databasecore.h"
#include "coremanager.h"
#include "Network/filedownloader.h"
#include "Utilities/fileextractor.h"
#include "wowcursexmlparser.h"

#include <QStandardPaths>
#include <QXmlStreamReader>
#include <QUrl>
#include <QDir>
#include <QSettings>
#include <QSet>

#include <algorithm>

#include <QDebug>

static constexpr char database_url[] = "http://clientupdate.curse.com/feed/Complete.xml.bz2";

DatabaseCore::DatabaseCore(CoreManager *parent) :
    AbstractCore(parent)
  , m_network(parent->network())
{
}

DatabaseCore::~DatabaseCore()
{
    qDeleteAll(m_addonList);
    qDeleteAll(m_installedList);
}

QVector<WowAddon*> DatabaseCore::addonList() const
{
    return m_addonList;
}

void DatabaseCore::refresh(bool isAsync)
{
    FileDownloader *downloader =  m_network->createFileDownloader();
    downloader->setUrl(database_url);
    downloader->setFileOverride(true);
    downloader->setDestination(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));

    connect(downloader, &FileDownloader::finished, [this, downloader](){
        QSettings settings;
        settings.setValue("wowCurseArchive", downloader->savedFileLocation());
        processCurseAddonArchive();
    });

    if (isAsync) {
        downloader->start();
    } else {
        downloader->startSync();
    }
}

// Not really optimized but it works.
void DatabaseCore::detect()
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
        for (auto addon : m_addonList) {
            for (auto folder : addon->folders()) {
                if (entry.startsWith(folder.name, Qt::CaseSensitivity::CaseInsensitive)) {
                    if (!tmpMap[entry].contains(addon->shortName())) {
                        tmpMap[entry] << addon->shortName();
                    }
                }
            }
        }
    }

    // tmpMap contains all the possible addon that could be installed;
    qDebug() << tmpMap;

    QSet<QString> possibleAddons;
    // Create a list of possible addon installed
    for (auto addonset : tmpMap) {
        for (auto addon : addonset) {
            if (!possibleAddons.contains(addon)) {
                possibleAddons << addon;
            }
        }
    }


    // We'll detect addon by matching the folders to what they contains.
    QVector<WowAddon*> finalAddonList;
    QVector<WowAddon*> badAddons;

    for (const QString &possibleAddon : possibleAddons) {

        // let's retrieve the AddOn using the shortname
        auto itObj = std::find_if(m_addonList.begin(), m_addonList.end(),
                                  [=](WowAddon* addon){
            return addon->shortName() == possibleAddon;
        });

        if (itObj == m_addonList.constEnd()) {
            qDebug() << "Addon not found :" << possibleAddon;
            continue;
        }

        WowAddon* addon = (*itObj);
        int addonFolderDetected = 0;

        // Compare the folder the addon install against the folder installed
        for (auto addonFolder : addon->folders()) {
            for (auto installedFolder : entries) {
                if (addonFolder.name == installedFolder) {
                    addonFolderDetected++;
                }
            }
        }
        if (addonFolderDetected == addon->folders().count()) {
//            qDebug() << "addon found " << addon->name();
            finalAddonList << addon;
        } else {
            badAddons << addon;
            qDebug() << "Bad number detected" << addon->name() << addon->folders().count() << addonFolderDetected;
        }
    }

    qDebug() << "number of addon detected" << finalAddonList.count();
    for (auto addon : finalAddonList) {
        qDebug() << addon->name();
    }

    qDebug() << "----------------------------------";
    for (auto addon : badAddons) {
        qDebug() << addon->name();
    }
}

void DatabaseCore::processCurseAddonArchive()
{
    QSettings settings;
    WowCurseXmlParser parser;
    QString xmlOutput = FileExtractor::bzip2FileToString(settings.value("wowCurseArchive").toString());
    m_addonList = parser.XmlToAddonList(xmlOutput);

    emit wowAddonListUpdated(m_addonList);
}
