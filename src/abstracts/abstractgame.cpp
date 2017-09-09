#include "abstractgame.h"

AbstractGame::AbstractGame(QObject* parent) :
    QObject(parent)
{

}

AbstractTask* AbstractGame::refresh()
{
    Q_UNREACHABLE();
}

AbstractTask* AbstractGame::detect()
{
    Q_UNREACHABLE();
}

QString AbstractGame::location() const
{
    Q_UNREACHABLE();
}

void AbstractGame::setLocation(const QString&)
{
    Q_UNREACHABLE();
}
