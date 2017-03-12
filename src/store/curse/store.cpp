#include "store.h"
#include "xmlparser.h"
#include "addon.h"
#include "downloadfilejob.h"
#include "utilities/fileextractor.h"
#include "network/networkcore.h"
#include "network/filedownloader.h"

#include "worldofwarcraft/worldofwarcraft.h"
#include "worldofwarcraft/addondetectjob.h"

#include <QStandardPaths>
#include <QXmlStreamReader>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QDataStream>
#include <QSettings>

#include <algorithm>

#include <QDebug>

using namespace Curse;

static constexpr char archive_url[] = "http://clientupdate.curse.com/feed/Complete.xml.bz2";

Store::Store(NetworkCore* network, QObject *parent) :
    AbstractStore(network, parent)
  , m_wow(new WorldOfWarcraft)
{
    connect(m_wow, &WorldOfWarcraft::refreshRequest, this, &Store::refresh);
}

Store::~Store()
{
    m_wow->deleteLater();
}

WorldOfWarcraft* Store::wow()
{
    return m_wow;
}

//AddonDetectJob* Store::detect()
//{
    //    if (isAsync && m_worker.isRunning()) {
    //        qDebug() << "job is already running";
    //        return nullptr;
    //    }

    //    AddonDetectJob* worker = new AddonDetectJob(m_wowLibrary);
    //    connect(worker, &AddonDetectJob::succcess, [this, &isAsync](const QVector<Addon*> &result){
    //        setWowInstalledAddons(result);
    //        saveInstalled();
    //        m_worker.quit();
    //        m_worker.wait();
    //        m_mutex.unlock();
    //    });

    //    connect(worker, &AddonDetectJob::error, [this] {
    //        m_mutex.unlock();
    //    });


    //    if (isAsync) {
    //        connect(&m_worker, &QThread::finished, worker, &QObject::deleteLater);
    //        m_mutex.lock();
    //        worker->moveToThread(&m_worker);
    //        m_worker.start();
    //        worker->run();
    //        return worker;
    //    }
//}

//void Store::update(Addon* addon)
//{
//    qDebug() << addon->name();
//    install(addon);
//}

//void Store::install(Addon* addon)
//{
//    qDebug() << addon->name();
//    qDebug() << addon->files().first().downloadUrl;
//    auto downloader = m_network->createFileDownloader();
//    downloader->setUrl(addon->files().first().downloadUrl);
//    downloader->setFileOverride(true);
//    downloader->setDestination(QStandardPaths::writableLocation(QStandardPaths::TempLocation));

//    connect(downloader, &FileDownloader::finished, [this, downloader](){
//        QSettings settings;
//        QString dest = QUrl(settings.value("wowDir").toString() + "/Interface/AddOns").toLocalFile();
//        FileExtractor::unzip(downloader->savedFileLocation(), dest);
//        downloader->deleteLater();
//        detect();
//    });
//    downloader->start();
//}

//bool Store::loadInstalled(bool isAsync)
//{
//    QFile loadFile(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/installed.json");
//    if (!loadFile.open(QIODevice::ReadOnly)) {
//        qWarning("Couldn't open save file.");
//        return false;
//    }
//    QByteArray data = loadFile.readAll();
//    const QStringList &savedAddonsList = QString::fromLocal8Bit(data).split(';');
//    const QVector<Addon*> &installedAddons = AddonDetectJob::getInstalledAddons(savedAddonsList, m_library);
//    setWowInstalledAddons(installedAddons);
//    qDebug() << installedAddons.count() << "addons loaded";
//    return true;
//}

//bool Store::saveInstalled()
//{
//    QList<QString> installedAddons;

//    for (Addon* addon : m_wowInstalled) {
//        installedAddons << addon->shortName();
//    }

//    QDir dir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
//    if (!dir.exists()) {
//        dir.mkpath(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
//    }


//    QFile saveFile(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/installed.json");
//    if (!saveFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        qWarning("Couldn't open save file.");
//        return false;
//    }
//    QString msg(installedAddons.join(';'));
//    saveFile.write(msg.toLocal8Bit());
//    saveFile.flush();
//    saveFile.close();
//    qDebug() << "Installed Addons saved";
//    return true;
//}

void Store::refresh()
{
    FileDownloader *downloader =  m_network->createFileDownloader();
    downloader->setUrl(archive_url);
    downloader->setFileOverride(true);
    downloader->setDestination(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));

    connect(downloader, &FileDownloader::finished, [this, downloader](){
        QSettings settings;
        settings.setValue("wowCurseArchive", downloader->savedFileLocation());
        loadLibraries();
        downloader->deleteLater();
    });

    downloader->start();
}

//void Store::setWowInstalledAddons(const QVector<Addon*>& installedAddons)
//{
//    m_wowInstalled = installedAddons;
//    emit wowInstalledListUpdated(installedAddons);
//}

void Store::loadLibraries()
{
    QSettings settings;
    XmlParser parser;
    QString xmlOutput = FileExtractor::bzip2FileToString(settings.value("wowCurseArchive").toString());

    m_library = parser.XmlToAddonList(xmlOutput);
    QVector<Addon*> wowLibrary;
    for (Addon* addon: m_library) {
        if (addon->gameId() == 1) {
            wowLibrary << addon;
        }
    }

    m_wow->setLibrary(wowLibrary);
}
