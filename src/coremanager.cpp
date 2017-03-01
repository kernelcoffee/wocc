#include "coremanager.h"
#include <QTimer>
#include <QDebug>

CoreManager::CoreManager(QObject *parent) :
    AbstractCore(parent)
  , m_network(new NetworkCore(this))
  , m_database(new DatabaseCore(this))
{
    QTimer::singleShot(0, this, &CoreManager::delayedInit);
}

CoreManager::~CoreManager()
{
    qDeleteAll(m_cores);
}

void CoreManager::init()
{
    m_console = new ConsoleCore(this);
#ifndef console_mode
    m_ui = new UiCore(this);
#endif

    m_cores  << m_network << m_database  << m_console;

#ifndef console_mode
    m_cores <<  m_ui;
    connect(m_console, &ConsoleCore::noCommandToProcess, [this](){ setConsoleMode(true); });
    connect(m_console, &ConsoleCore::noCommandToProcess, m_ui, &UiCore::startX, Qt::QueuedConnection);
#endif


    for (auto core : m_cores) {
        qDebug() << core << "init";
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
}

bool CoreManager::consoleMode()
{
    return m_consoleMode;
}

NetworkCore *CoreManager::network() const
{
    return m_network;
}

DatabaseCore*CoreManager::database() const
{
    return m_database;
}

void CoreManager::delayedInit()
{
    for (auto core : m_cores) {
        core->delayedInit();
    }
}

void CoreManager::aboutToQuit()
{
    for (auto core : m_cores) {
        core->aboutToQuit();
    }
}

void CoreManager::setConsoleMode(bool consoleMode)
{
    m_consoleMode = consoleMode;
}

