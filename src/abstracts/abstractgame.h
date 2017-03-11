#ifndef ABSTRACTGAME_H
#define ABSTRACTGAME_H

#include <QObject>

class AbstractGame : public QObject
{
public:
    AbstractGame(QObject *parent = 0);
};

#endif // ABSTRACTGAME_H
