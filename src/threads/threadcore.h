#ifndef THREADCORE_H
#define THREADCORE_H

#include "abstracts/abstractcore.h"

class CoreManager;
class AbstractTask;
class QThread;

class ThreadCore : public AbstractCore
{
    Q_OBJECT

    Q_PROPERTY(QList<AbstractTask*> tasks READ tasks NOTIFY tasksChanged)
public:
    explicit ThreadCore(CoreManager* parent = nullptr);

    QList<AbstractTask*> tasks() const;

public slots:
    bool addTask(AbstractTask* task);
    virtual void aboutToQuit() override;

signals:
    void tasksChanged(const QList<AbstractTask*>& tasks);

private:
    QList<AbstractTask*> m_tasks;
    QList<QThread*> m_pool;
};

#endif // THREADCORE_H
