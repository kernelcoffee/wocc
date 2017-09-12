#ifndef ABSTRACTSTORE_H
#define ABSTRACTSTORE_H

#include <QObject>

class NetworkCore;
class ThreadCore;

class AbstractStore : public QObject
{
    Q_OBJECT
public:
    explicit AbstractStore(QObject* parent = nullptr);
};

#endif // ABSTRACTSTORE_H
