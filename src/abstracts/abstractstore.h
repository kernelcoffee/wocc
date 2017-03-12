#ifndef ABSTRACTSTORE_H
#define ABSTRACTSTORE_H

#include <QObject>

class NetworkCore;

class AbstractStore : public QObject
{
    Q_OBJECT
public:
    explicit AbstractStore(NetworkCore* network, QObject *parent = nullptr);

protected:
    NetworkCore* m_network;
};

#endif // ABSTRACTSTORE_H
