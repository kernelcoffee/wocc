#include "abstracttask.h"

AbstractTask::AbstractTask(QObject* parent) :
    QObject(parent)
{

}

QString AbstractTask::name() const
{
    return m_name;
}

uint AbstractTask::progress() const
{
    return m_progress;
}

AbstractTask::Status AbstractTask::status() const
{
    return m_status;
}

void AbstractTask::setProgress(uint progress)
{
    if (m_progress == progress)
        return;

    m_progress = progress;
    emit progressChanged(m_progress);
}

void AbstractTask::setStatus(AbstractTask::Status status)
{
    if (m_status == status)
        return;

    m_status = status;
    emit statusChanged(m_status);
}
