#include "worldofwarcraft.h"

#include <QDebug>
using namespace Curse;

WorldOfWarcraft::WorldOfWarcraft(QObject *parent) :
    AbstractGame(parent)
{

}

WorldOfWarcraft::~WorldOfWarcraft()
{
//    qDeleteAll(m_library);
}

void WorldOfWarcraft::refresh()
{
    emit refreshRequest();
}

void WorldOfWarcraft::detect()
{
//    if (isAsync && m_workerThread.isRunning()) {
//        qDebug() << "job is already running";
//        return nullptr;
//    }

//    AddonDetectJob* worker = new AddonDetectJob(m_wowLibrary);
//    connect(worker, &AddonDetectJob::succcess, [this, &isAsync](const QVector<Addon*> &result){
//        setWowInstalledAddons(result);
//        saveInstalled();
//        m_workerThread.quit();
//        m_workerThread.wait();
//        m_mutex.unlock();
//    });

//    connect(worker, &AddonDetectJob::error, [this] {
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
//    return nullptr;

}

void WorldOfWarcraft::setLibrary(const QVector<Addon*> &library)
{
    m_library = library;
    qDebug() << "Wow library updated with " << m_library.count() << "addons";
    emit libraryUpdated();
}
