#include "threadcore.h"
#include "coremanager.h"

#include "abstracts/abstracttask.h"

#include <QDebug>

ThreadCore::ThreadCore(CoreManager* parent) :
    AbstractCore(parent)
{

}

QList<AbstractTask*> ThreadCore::tasks() const
{
    return m_tasks;
}

void ThreadCore::addTask(AbstractTask* task)
{
    for (auto existing : m_tasks) {
        if (existing == task) {
            qDebug() << "Task" << task->name() << "Already exist";
            return;
        }
    }
    m_tasks.append(task);
}
