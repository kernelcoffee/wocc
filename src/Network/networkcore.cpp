#include "networkcore.h"
#include "filedownloader.h"

NetworkCore::NetworkCore(QObject *parent) :
    AbstractCore(parent)
{

}

void NetworkCore::init()
{

}

void NetworkCore::initSettings()
{

}

FileDownloader *NetworkCore::createFileDownloader()
{
    return new FileDownloader(m_manager);
}

void NetworkCore::aboutToQuit()
{

}
