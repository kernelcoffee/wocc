#include "databasecore.h"
#include "coremanager.h"

DatabaseCore::DatabaseCore(CoreManager *parent) :
    AbstractCore(parent)
  , m_network(parent->network())
{

}

void DatabaseCore::init()
{

}

void DatabaseCore::initSettings()
{

}

void DatabaseCore::aboutToQuit()
{

}

void DatabaseCore::update()
{
}
