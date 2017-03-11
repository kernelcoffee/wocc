#include "store.h"
#include "network/networkcore.h"
#include "network/filedownloader.h"
#include "utilities/fileextractor.h"
#include "xmlparser.h"
#include "addon.h"

#include "store/curse/worldofwarcraft/wowaddondetectionworker.h"

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
    QObject(parent)
  , m_network(network)
{
}

Store::~Store()
{
    qDeleteAll(m_wowLibrary);
}

QVector<Addon*> Store::wowLibrary() const
{
    return m_wowLibrary;
}

FileDownloader* Store::refresh(bool isAsync)
{
    FileDownloader *downloader =  m_network->createFileDownloader();
    downloader->setUrl(archive_url);
    downloader->setFileOverride(true);
    downloader->setDestination(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));

    connect(downloader, &FileDownloader::finished, [this, downloader, &isAsync](){
        QSettings settings;
        settings.setValue("wowCurseArchive", downloader->savedFileLocation());
        loadLibrary(isAsync);
        downloader->deleteLater();
    });

    if (isAsync) {
        downloader->start();
    } else {
        downloader->startSync();
    }
    return downloader;
}

WowAddonDetectionWorker* Store::detect(bool isAsync)
{
    if (isAsync && m_workerThread.isRunning()) {
        qDebug() << "job is already running";
        return nullptr;
    }

    WowAddonDetectionWorker* worker = new WowAddonDetectionWorker(m_wowLibrary);
    connect(worker, &WowAddonDetectionWorker::succcess, [this, &isAsync](const QVector<Addon*> &result){
        setWowInstalledAddons(result);
        saveInstalled();
        m_workerThread.quit();
        m_workerThread.wait();
        m_mutex.unlock();
    });

    connect(worker, &WowAddonDetectionWorker::error, [this] {
        m_mutex.unlock();
    });


    if (isAsync) {
        connect(&m_workerThread, &QThread::finished, worker, &QObject::deleteLater);
        m_mutex.lock();
        worker->moveToThread(&m_workerThread);
        m_workerThread.start();
        worker->run();
        return worker;
    }

    worker->run();
    worker->deleteLater();
    return nullptr;
}

void Store::update(Addon* addon)
{
    qDebug() << addon->name();
    install(addon);
}

void Store::install(Addon* addon)
{
    qDebug() << addon->name();
    qDebug() << addon->files().first().downloadUrl;
    auto downloader = m_network->createFileDownloader();
    downloader->setUrl(addon->files().first().downloadUrl);
    downloader->setFileOverride(true);
    downloader->setDestination(QStandardPaths::writableLocation(QStandardPaths::TempLocation));

    connect(downloader, &FileDownloader::finished, [this, downloader](){
        QSettings settings;
        QString dest = QUrl(settings.value("wowDir").toString() + "/Interface/AddOns").toLocalFile();
        FileExtractor::unzip(downloader->savedFileLocation(), dest);
        downloader->deleteLater();
        detect();
    });
    downloader->start();
}

void Store::remove(Addon* addon)
{

}

void Store::loadLibrary(bool isAsync)
{
    if (isAsync && m_workerThread.isRunning()) {
        qDebug() << "job is already running";
        return;
    }

    QSettings settings;
    XmlParser parser;
    QString xmlOutput = FileExtractor::bzip2FileToString(settings.value("wowCurseArchive").toString());

    m_wowLibrary = parser.XmlToAddonList(xmlOutput);

    emit wowLibraryUpdated(m_wowLibrary);
}

bool Store::loadInstalled(bool isAsync)
{
    QFile loadFile(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/installed.json");
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }
    QByteArray data = loadFile.readAll();
    const QStringList &savedAddonsList = QString::fromLocal8Bit(data).split(';');
    const QVector<Addon*> &installedAddons = WowAddonDetectionWorker::getInstalledAddons(savedAddonsList, m_wowLibrary);
    setWowInstalledAddons(installedAddons);
    qDebug() << installedAddons.count() << "addons loaded";
    return true;
}

bool Store::saveInstalled()
{
    QList<QString> installedAddons;

    for (Addon* addon : m_wowInstalled) {
        installedAddons << addon->shortName();
    }

    QDir dir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    if (!dir.exists()) {
        dir.mkpath(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    }


    QFile saveFile(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/installed.json");
    if (!saveFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Couldn't open save file.");
        return false;
    }
    QString msg(installedAddons.join(';'));
    saveFile.write(msg.toLocal8Bit());
    saveFile.flush();
    saveFile.close();
    qDebug() << "Installed Addons saved";
    return true;
}

void Store::setWowInstalledAddons(const QVector<Addon*>& installedAddons)
{
    m_wowInstalled = installedAddons;
    emit wowInstalledListUpdated(installedAddons);
}
