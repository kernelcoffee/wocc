#ifndef THREADCORE_H
#define THREADCORE_H

#include "abstracts/abstractcore.h"

class CoreManager;
class AbstractTask;

class ThreadCore : public AbstractCore
{
    Q_OBJECT

    Q_PROPERTY(QList<AbstractTask*> tasks READ tasks NOTIFY tasksChanged)
public:
    explicit ThreadCore(CoreManager* parent = nullptr);

    void AddTask();
    QList<AbstractTask*> tasks() const;

public slots:
    void addTask(AbstractTask* task);

signals:
    void tasksChanged(const QList<AbstractTask*>& tasks);

private:
    QList<AbstractTask*> m_tasks;
};

#endif // THREADCORE_H
