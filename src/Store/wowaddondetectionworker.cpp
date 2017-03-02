#include "wowaddondetectionworker.h"
#include "wowaddon.h"

#include <QSettings>
#include <QDir>
#include <QUrl>
#include <QSet>

#include <QDebug>

WowAddonDetectionWorker::WowAddonDetectionWorker(const QVector<WowAddon*> &library, QObject *parent) :
    QObject(parent)
  , m_library(library)
{
    qDebug() << m_library.count();
}

uint WowAddonDetectionWorker::progress() const
{
    return m_progress;
}

QStringList WowAddonDetectionWorker::getPossibleAddons(const QVector<WowAddon*>& library)
{
    QSettings settings;

    const QString &addonPath = settings.value("wowDir").toString() + "/Interface/AddOns";
    QDir dir(QUrl(addonPath).toLocalFile());

    if (!dir.exists()) {
        qDebug()  << "Addon path doesn't exist";
        return QStringList();
    }

    if (library.isEmpty()) {
        qDebug() << "Library is empty";
        return QStringList();
    }

    QStringList entries = dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs);

    QMap<QString, QStringList> tmpMap;

    // Let's create a map of addons per folder installed
    for (auto entry : entries) {
        for (auto addon : library) {
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

    QStringList possibleAddons;
    // Create a list of possible addon installed
    for (auto addonset : tmpMap) {
        for (auto addon : addonset) {
            if (!possibleAddons.contains(addon)) {
                possibleAddons << addon;
            }
        }
    }

    return possibleAddons;
}

QVector<WowAddon*> WowAddonDetectionWorker::getInstalledAddons(const QStringList& possibleAddons, const QVector<WowAddon*>& library)
{
    // We'll detect addon by matching the folders to what they contains.
    QVector<WowAddon*> badAddons;
    QVector<WowAddon*> installedAddons;
    QSettings settings;

    const QString &addonPath = settings.value("wowDir").toString() + "/Interface/AddOns";

    QDir dir(QUrl(addonPath).toLocalFile());
    QStringList entries = dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs);

    for (const QString &possibleAddon : possibleAddons) {

        // let's retrieve the AddOn using the shortname
        auto itObj = std::find_if(library.begin(), library.end(), [=](WowAddon* addon){
            return addon->shortName() == possibleAddon;
        });

        if (itObj == library.constEnd()) {
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
            installedAddons << addon;
        } else {
            badAddons << addon;
        }
    }

    qDebug() << "Addon detected" << installedAddons.count();
    qDebug() << "addon rejected" << badAddons.count();

    return installedAddons;
}


// Not really optimized but it works.
void WowAddonDetectionWorker::run()
{
    const QStringList &possibleAddons = getPossibleAddons(m_library);
    qDebug() << "Premiminary addon detection :" << possibleAddons.count();

    const QVector<WowAddon*> &installedAddons = getInstalledAddons(possibleAddons, m_library);

    emit succcess(installedAddons);
}
