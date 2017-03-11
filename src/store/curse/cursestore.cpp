#include "cursestore.h"
#include "Network/networkcore.h"
#include "Network/filedownloader.h"
#include "Utilities/fileextractor.h"
#include "wowcursexmlparser.h"
#include "wowaddon.h"

#include "wowaddondetectionworker.h"

#include <QStandardPaths>
#include <QXmlStreamReader>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QDataStream>
#include <QSettings>

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

QVector<WowAddon*> CurseStore::wowLibrary() const
{
    return m_wowLibrary;
}

FileDownloader* CurseStore::refresh(bool isAsync)
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

WowAddonDetectionWorker* CurseStore::detect(bool isAsync)
{
    if (isAsync && m_workerThread.isRunning()) {
        qDebug() << "job is already running";
        return nullptr;
    }

    WowAddonDetectionWorker* worker = new WowAddonDetectionWorker(m_wowLibrary);
    connect(worker, &WowAddonDetectionWorker::succcess, [this, &isAsync](const QVector<WowAddon*> &result){
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

void CurseStore::update(WowAddon* addon)
{
    qDebug() << addon->name();
    install(addon);
}

void CurseStore::install(WowAddon* addon)
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

void CurseStore::remove(WowAddon* addon)
{

}

void CurseStore::loadLibrary(bool isAsync)
{
    if (isAsync && m_workerThread.isRunning()) {
        qDebug() << "job is already running";
        return;
    }

    QSettings settings;
    WowCurseXmlParser parser;
    QString xmlOutput = FileExtractor::bzip2FileToString(settings.value("wowCurseArchive").toString());

    m_wowLibrary = parser.XmlToAddonList(xmlOutput);

    emit wowLibraryUpdated(m_wowLibrary);
}

bool CurseStore::loadInstalled(bool isAsync)
{
    QFile loadFile(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/installed.json");
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }
    QByteArray data = loadFile.readAll();
    const QStringList &savedAddonsList = QString::fromLocal8Bit(data).split(';');
    const QVector<WowAddon*> &installedAddons = WowAddonDetectionWorker::getInstalledAddons(savedAddonsList, m_wowLibrary);
    setWowInstalledAddons(installedAddons);
    qDebug() << installedAddons.count() << "addons loaded";
    return true;
}

bool CurseStore::saveInstalled()
{
    QList<QString> installedAddons;

    for (WowAddon* addon : m_wowInstalled) {
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

void CurseStore::setWowInstalledAddons(const QVector<WowAddon*>& installedAddons)
{
    m_wowInstalled = installedAddons;
    emit wowInstalledListUpdated(installedAddons);
}
