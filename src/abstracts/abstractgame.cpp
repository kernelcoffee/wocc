#include "abstractgame.h"

AbstractGame::AbstractGame(QObject *parent) :
    QObject(parent)
{

}

AbstractWorker *AbstractGame::refresh()
{
    Q_UNREACHABLE();
}

AbstractWorker *AbstractGame::detect()
{
    Q_UNREACHABLE();
}

QString AbstractGame::location() const
{
    Q_UNREACHABLE();
}

void AbstractGame::setLocation(const QString& location)
{
    Q_UNREACHABLE();
}
