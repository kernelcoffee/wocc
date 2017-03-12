#ifndef WORLDOFWARCRAFT_H
#define WORLDOFWARCRAFT_H

#include "abstracts/abstractgame.h"

#include <QVector>
#include <QThread>
#include <QMutex>

namespace Curse {

class Addon;
class DownloadFile;

class WorldOfWarcraft : public AbstractGame
{
    Q_OBJECT
public:
    explicit WorldOfWarcraft(QObject *parent = 0);
    ~WorldOfWarcraft();

    virtual void refresh() override;
    virtual void detect() override;

signals:
    void refreshRequest();
    void libraryUpdated(const QVector<Addon*> &library);

public slots:
    void setLibrary(const QVector<Addon*> &library);

private:
    QVector<Addon*> m_library;

    QThread m_worker;
    QMutex m_mutex;
};

}

#endif // WORLDOFWARCRAFT_H
