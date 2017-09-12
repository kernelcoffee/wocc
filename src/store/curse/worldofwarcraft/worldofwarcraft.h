#ifndef WORLDOFWARCRAFT_H
#define WORLDOFWARCRAFT_H

#include "abstracts/abstractgame.h"

#include <QVector>
#include <QThread>
#include <QMutex>

class ThreadCore;
class NetworkCore;
class DownloadFile;

namespace Curse {

class Addon;

class WorldOfWarcraft : public AbstractGame
{
    Q_OBJECT
public:
    explicit WorldOfWarcraft(QObject* parent = 0);

    void init(NetworkCore* network, ThreadCore* threads);

    Q_INVOKABLE virtual AbstractTask* refresh() override;
    Q_INVOKABLE virtual AbstractTask* detect() override;

    Q_INVOKABLE void install(Curse::Addon* addon);
    Q_INVOKABLE Addon* getAddonById(uint id);
    virtual QString location() const override;

    QVector<Addon*> library() const;

signals:
    void libraryUpdated(const QVector<Addon*>& library);

public slots:
    void setLibrary(const QVector<Addon*>& library);
    virtual void setLocation(const QString& location);

private:
    void updateLibrary(const QVector<Curse::Addon*>& addons);

    ThreadCore* m_threads;
    NetworkCore* m_network;
    QVector<Addon*> m_library;

    QThread m_worker;
    QMutex m_mutex;
};

}

#endif // WORLDOFWARCRAFT_H
