#include "worldofwarcraft.h"
#include "store/curse/addon.h"
#include "threads/threadcore.h"
#include "network/networkcore.h"

#include "detecttask.h"
#include "installtask.h"

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

void WorldOfWarcraft::init(NetworkCore* network, ThreadCore* threads)
{
    m_network = network;
    m_threads = threads;
}

AbstractTask* WorldOfWarcraft::refresh()
{
    // Refresh is done in the store class for this game.
    Q_UNREACHABLE();
    return nullptr;
}

AbstractTask* WorldOfWarcraft::detect()
{
    if (m_worker.isRunning()) {
        qDebug() << "job is already running";
        return nullptr;
    }

    DetectTask* task = new DetectTask(m_library);
    connect(task, &DetectTask::succcess, this, &WorldOfWarcraft::updateLibrary);

    m_threads->addTask(task);
    return task;
}

void WorldOfWarcraft::install(Curse::Addon* addon)
{
    if (addon->isInstalled()) {
        qDebug() << addon->name() << "Already installed";
    }

    for (const Addon::Dependency& dep : addon->dependencies()) {
        if (dep.addon == nullptr) {
            continue;
        }
        if (dep.category == "required") {
            install(dep.addon);
        }
    }
    m_threads->addTask(new InstallTask(addon, m_network->createFileDownloader()));
}

Addon* WorldOfWarcraft::getAddonById(uint id)
{
    for (Addon* addon : m_library) {
        if (addon->id() == id) {
            qDebug() << "Addon found : " << addon->shortName();
        }
    }
    qDebug() << "Addon not found";
    return nullptr;
}

QString WorldOfWarcraft::location() const
{
    return m_location;
}

QVector<Addon*> WorldOfWarcraft::library() const
{
    return m_library;
}

void WorldOfWarcraft::setLibrary(const QVector<Curse::Addon*>& library)
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

void WorldOfWarcraft::updateLibrary(const QVector<Curse::Addon*>& addons)
{
    for (auto addon : addons) {
        addon->print();
    }
}

//bool Store::loadInstalled(bool isAsync)
//{
//    QFile loadFile(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/installed.json");
//    if (!loadFile.open(QIODevice::ReadOnly)) {
//        qWarning("Couldn't open save file.");
//        return false;
//    }
//    QByteArray data = loadFile.readAll();
//    const QStringList &savedAddonsList = QString::fromLocal8Bit(data).split(';');
//    const QVector<Addon*> &installedAddons = DetectTask::getInstalledAddons(savedAddonsList, m_library);
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
