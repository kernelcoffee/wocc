#include "consolecore.h"

#include <QDebug>

ConsoleCore::ConsoleCore(QObject *parent) :
    AbstractCore(parent)
{

}

void ConsoleCore::init()
{

}

void ConsoleCore::initSettings()
{

}

void ConsoleCore::initArguments(QCommandLineParser &parser)
{
    parser.addPositionalArgument("command", tr("command to run"));
}

void ConsoleCore::processArguments(QCommandLineParser &parser)
{
    const QStringList args = parser.positionalArguments();

    qDebug() << args;
}

void ConsoleCore::aboutToQuit()
{

}

