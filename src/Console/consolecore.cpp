#include "consolecore.h"

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

void ConsoleCore::initArguments(QCommandLineParser &cmd)
{
    Q_UNUSED(cmd)
}

void ConsoleCore::processArguments(QCommandLineParser &cmd)
{
    Q_UNUSED(cmd)
}

void ConsoleCore::aboutToQuit()
{

}

