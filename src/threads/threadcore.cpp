#include "threadcore.h"
#include "coremanager.h"

#include "abstracts/abstracttask.h"

#include <QThread>
#include <QDebug>

ThreadCore::ThreadCore(CoreManager* parent) :
    AbstractCore(parent)
    , m_queuedThead(new QThread(this))
{
    qRegisterMetaType<AbstractTask::Status>("AbstractTask::Status");


    connect(this, &ThreadCore::tasksChanged, this, &ThreadCore::processNextTask);
}

QList<AbstractTask*> ThreadCore::tasks() const
{
    return m_tasks;
}

bool ThreadCore::addTask(AbstractTask* task)
{
    for (auto existing : m_tasks) {
        if (existing == task || (task->isUnique() && existing->name() == task->name())) {
            qDebug() << QString("Task %1 already exist").arg(task->name());
            task->deleteLater();
            return false;
        }
    }

    qDebug() << "Adding to queue" << task->name();
    m_tasks.append(task);
    emit tasksChanged(m_tasks);

    return true;
}

void ThreadCore::aboutToQuit()
{
    for (AbstractTask* task : m_tasks) {
        qDebug() << "Cancelling task : " << task->name();
        task->cancel();
    }

    m_queuedThead->quit();
    m_queuedThead->wait();
    m_queuedThead->deleteLater();

    for (QThread* thread : m_pool) {
        qDebug() << "Terminating thread : " << thread;
        thread->quit();;
        thread->wait();
        thread->deleteLater();
    }
}

void ThreadCore::processNextTask()
{
    qDebug() << "processNextTask";
    if (!m_queuedThead->isRunning()) {
        for (AbstractTask* task : m_tasks) {
            if (task->status() == AbstractTask::Idle) {
                m_queuedTask = task;
                connect(task, &AbstractTask::statusChanged, this, &ThreadCore::processTask);
                task->moveToThread(m_queuedThead);

                if (!m_queuedThead->isRunning()) {
                    m_queuedThead->start();
                }

                m_queuedTask->start();
                qDebug() << "Starting : " << task->name();
                return;
            }
        }
    }
}

void ThreadCore::processTask()
{
    qDebug() << "Task status changed : " << m_queuedTask->name();

    if (m_queuedTask->status() == AbstractTask::Running) {
        return;
    }

    if (m_queuedTask->isAutoDelete()) {
        auto task = m_tasks.takeAt(m_tasks.indexOf(m_queuedTask));
        task->deleteLater();
    }

    m_queuedThead->quit();
    m_queuedThead->wait();
    processNextTask();
}
