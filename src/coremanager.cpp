#include "coremanager.h"

CoreManager::CoreManager(QObject *parent) :
    AbstractCore(parent)
#ifndef nox_mode
  , m_ui(new UiCore(this))
#else
  , m_console(new ConsoleCore(this))
#endif
{

#ifndef nox_mode
    m_cores["ui"] = m_ui;
#else
    m_cores["console"] = m_console;
#endif

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

void CoreManager::initArguments(QCommandLineParser &cmd)
{
    cmd.addHelpOption();
    cmd.addVersionOption();

    for (auto core : m_cores) {
        core->initArguments(cmd);
    }
}

void CoreManager::processArguments(QCommandLineParser &cmd)
{
    for (auto core : m_cores) {
        core->processArguments(cmd);
    }
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

