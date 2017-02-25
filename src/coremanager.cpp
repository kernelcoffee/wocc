#include "coremanager.h"
#include <QTimer>

CoreManager::CoreManager(QObject *parent) :
    AbstractCore(parent)
#ifndef console_mode
  , m_ui(new UiCore(this))
#endif
  , m_network(new NetworkCore(this))
  , m_database(new DatabaseCore(this))
  , m_console(new ConsoleCore(this))
{

#ifndef console_mode
    m_cores <<  m_ui;
#endif

    QTimer::singleShot(0, this, &CoreManager::delayedInit);
    m_cores << m_network << m_database << m_console;
}

CoreManager::~CoreManager()
{
    qDeleteAll(m_cores);
}

void CoreManager::init()
{
    for (auto core : m_cores) {
        core->init();
    }
}

void CoreManager::initSettings()
{
    for (auto core : m_cores) {
        core->initSettings();
    }
}

void CoreManager::initArguments(QCommandLineParser &parser)
{
    parser.addHelpOption();
    parser.addVersionOption();

    for (auto core : m_cores) {
        core->initArguments(parser);
    }
}

void CoreManager::processArguments(QCommandLineParser &parser)
{
    for (auto core : m_cores) {
        core->processArguments(parser);
    }
#ifdef console_mode
    qApp->quit();
#endif
}

NetworkCore *CoreManager::network() const
{
    return m_network;
}

void CoreManager::delayedInit()
{
    for (auto core : m_cores) {
        core->delayedInit();
    }
    emit initDone();
}

void CoreManager::aboutToQuit()
{
    for (auto core : m_cores) {
        core->aboutToQuit();
    }
}

