#include "consolecore.h"
#include "coremanager.h"
#include "store/storecore.h"
#include "store/curse/addon.h"
#include "store/curse/store.h"
#include "store/curse/worldofwarcraft/worldofwarcraft.h"

#include <QDebug>
#include <QEventLoop>

ConsoleCore::ConsoleCore(CoreManager *parent) :
    AbstractCore(parent)
  , m_cores(parent)
  , m_stores(parent->stores())
{
}

void ConsoleCore::init()
{
    m_commandMap["update"] = [this](){update();};
    m_commandMap["detect"] = [this](){detect();};
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
        m_cores->setConsoleMode(true);
        emit noCommandToProcess();
        return;
    }
}

void ConsoleCore::delayedInit()
{
    if (m_args.count() == 0) {
#ifdef console_mode
        qApp->exit();
#endif
        return;
    }

    const QString& command = m_args.at(0);

    if (!m_commandMap.contains(command)) {
        qWarning() << "Command not found";
        qApp->exit();
        return;
    }

    qDebug() << command;
    m_commandMap[command]();

    qApp->exit();
}

void ConsoleCore::update()
{
    qDebug() << "update";
    QEventLoop loop;
    Curse::WorldOfWarcraft* wow = m_stores->curse()->wow();
    connect(wow, &Curse::WorldOfWarcraft::libraryUpdated,
            &loop, &QEventLoop::quit);
    wow->refresh();
    loop.exec();
}

void ConsoleCore::detect()
{
    qDebug() << "detect";
//    m_stores->curse()->refresh(false);
//    m_stores->curse()->detect();
}
