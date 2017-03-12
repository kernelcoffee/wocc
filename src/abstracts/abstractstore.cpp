#include "abstractstore.h"
#include "network/networkcore.h"

AbstractStore::AbstractStore(NetworkCore* network, QObject *parent) :
    QObject(parent)
  , m_network(network)
{

}
