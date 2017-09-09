#include "abstractjob.h"

AbstractJob::AbstractJob(QObject* parent) :
    QObject(parent)
{

}

QString AbstractJob::name() const
{
    return m_name;
}
