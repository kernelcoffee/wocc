#include "networkcore.h"
#include "filedownloader.h"

NetworkCore::NetworkCore(QObject *parent) :
    AbstractCore(parent)
{

}

FileDownloader* NetworkCore::createFileDownloader()
{
    return new FileDownloader(&m_manager);
}
