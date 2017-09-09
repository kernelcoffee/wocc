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

bool AbstractTask::isAutoDelete()
{
    return m_autoDelete;
}

void AbstractTask::start()
{
    Q_UNREACHABLE();
}

void AbstractTask::pause()
{
    Q_UNREACHABLE();
}

void AbstractTask::cancel()
{
    Q_UNREACHABLE();
}

bool AbstractTask::isUnique() const
{
    return m_isUnique;
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

void AbstractTask::setAutoDelete(bool autoDelete)
{
    if (m_autoDelete == autoDelete)
        return;

    m_autoDelete = autoDelete;
    emit autoDeleteChanged(m_autoDelete);
}

void AbstractTask::setIsUnique(bool isUnique)
{
    if (m_isUnique == isUnique)
        return;

    m_isUnique = isUnique;
    emit isUniqueChanged(m_isUnique);
}
