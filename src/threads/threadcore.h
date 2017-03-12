#ifndef THREADCORE_H
#define THREADCORE_H

#include "abstracts/abstractcore.h"

class CoreManager;
class Worker;

class ThreadCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit ThreadCore(CoreManager *parent = nullptr);

    Worker* getNewWorker();

private:
    QList<Worker*> m_worker;
};

#endif // THREADCORE_H
