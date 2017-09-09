#ifndef ABSTRACTSTORE_H
#define ABSTRACTSTORE_H

#include <QObject>

class NetworkCore;

class AbstractStore : public QObject
{
    Q_OBJECT
public:
    explicit AbstractStore(QObject* parent = nullptr);

    void init(NetworkCore* network);

protected:
    NetworkCore* m_network;
};

#endif // ABSTRACTSTORE_H
