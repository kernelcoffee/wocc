#include "abstractstore.h"
#include "network/networkcore.h"

AbstractStore::AbstractStore(QObject *parent) :
    QObject(parent)
{

}

void AbstractStore::init(NetworkCore *network)
{
    m_network = network;
}
