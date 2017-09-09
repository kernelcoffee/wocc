#include "worldofwarcraft.h"
#include "addondetectjob.h"
#include "store/curse/addon.h"

#include <QSettings>
#include <QStandardPaths>

#include <QDebug>

using namespace Curse;

static constexpr char addOnPath[] = "";

WorldOfWarcraft::WorldOfWarcraft(QObject* parent) :
    AbstractGame(parent)
{
    QSettings settings;

    settings.beginGroup("WorldOfWarcraft");
    m_location = settings.value("location",
                                QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).toString();
    settings.endGroup();
}

AbstractWorker* WorldOfWarcraft::refresh()
{
    // Refresh is done in the store class for this game.
    Q_UNREACHABLE();
    return nullptr;
}

AbstractWorker* WorldOfWarcraft::detect()
{
    return nullptr;
//    if (m_workerThread.isRunning()) {
//        qDebug() << "job is already running";
//        return nullptr;
//    }

//    AddonDetectJob* worker = new AddonDetectJob(m_wowLibrary);
//    connect(worker, &AddonDetectJob::succcess, [this](const QVector<Addon*> &result){
//        setWowInstalledAddons(result);
//        saveInstalled();
//        m_workerThread.quit();
//        m_workerThread.wait();
//        m_mutex.unlock();
//    });

//    connect(worker, &AddonDetectJob::error, [this]() {
//        m_mutex.unlock();
//    });


//    if (isAsync) {
//        connect(&m_workerThread, &QThread::finished, worker, &QObject::deleteLater);
//        m_mutex.lock();
//        worker->moveToThread(&m_workerThread);
//        m_workerThread.start();
//        worker->run();
//        return worker;
//    }

//    worker->run();
//    worker->deleteLater();
    //    return worker;
}

void WorldOfWarcraft::install(Curse::Addon* addon)
{
    addon->printContent();
}

QString WorldOfWarcraft::location() const
{
    return m_location;
}

void WorldOfWarcraft::setLibrary(const QVector<Addon*>& library)
{
    m_library = library;
    qDebug() << "Wow library updated with " << m_library.count() << "addons";
    emit libraryUpdated(library);
}

void WorldOfWarcraft::setLocation(const QString& location)
{
    if (m_location == location)
        return;

    QSettings settings;

    settings.beginGroup("WorldOfWarcraft");
    settings.setValue("location", location);
    settings.endGroup();

    m_location = location;
    emit locationChanged(m_location);
}

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
