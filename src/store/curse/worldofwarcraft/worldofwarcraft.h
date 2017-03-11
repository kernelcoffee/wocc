#ifndef WORLDOFWARCRAFT_H
#define WORLDOFWARCRAFT_H

#include "abstracts/abstractgame.h"
#include "store/curse/addon.h"

class WorldOfWarcraft : public AbstractGame
{
    Q_OBJECT
public:
    explicit WorldOfWarcraft(QObject *parent = 0);

    void update(Curse::Addon* addon);
    void install(Curse::Addon* addon);
    void remove(Curse::Addon* addon);

public slots:
};

#endif // WORLDOFWARCRAFT_H
