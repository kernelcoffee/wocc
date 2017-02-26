#include "consolecore.h"
#include "coremanager.h"

#include <QDebug>

ConsoleCore::ConsoleCore(CoreManager *parent) :
    AbstractCore(parent)
  , m_database(parent->database())
{

}

void ConsoleCore::initArguments(QCommandLineParser &parser)
{
    parser.addPositionalArgument("command", tr("command to run"));
}

void ConsoleCore::processArguments(QCommandLineParser &parser)
{
    m_args = parser.positionalArguments();

    qDebug() << m_args;

    if (m_args.count() == 0) {
        emit noCommandToProcess();
        return;
    }
}

void ConsoleCore::aboutToQuit()
{
    qDebug() << "About to quit";
}

void ConsoleCore::delayedInit()
{
    m_database->update(false);
    qApp->exit();
}
