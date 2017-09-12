#include "threadcore.h"
#include "coremanager.h"

#include "abstracts/abstracttask.h"

#include <QThread>
#include <QDebug>

ThreadCore::ThreadCore(CoreManager* parent) :
    AbstractCore(parent)
{

}

QList<AbstractTask*> ThreadCore::tasks() const
{
    return m_tasks;
}

bool ThreadCore::addTask(AbstractTask* task)
{
    for (auto existing : m_tasks) {
        if (existing == task) {
            qDebug() << QString("Task %1 already exist").arg(task->name());
            return false;
        }
    }
    QThread* thread = new QThread(this);

    m_tasks.append(task);
    emit tasksChanged(m_tasks);

    task->moveToThread(thread);
    m_pool.append(thread);

    if (task->isAutoDelete()) {
        connect(thread, &QThread::finished, task, &AbstractTask::deleteLater);
    }

    thread->start();
    return true;
}

void ThreadCore::aboutToQuit()
{
    qDebug() << "Cleaning threads";
    for (AbstractTask* task : m_tasks) {
        task->cancel();
    }

    for (QThread* thread : m_pool) {
        qDebug() << "Terminating thread : " << thread;
        thread->quit();;
        thread->wait();
        thread->deleteLater();
    }
}
