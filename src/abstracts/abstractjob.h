#ifndef ABSTRACTJOB_H
#define ABSTRACTJOB_H

#include <QObject>

class AbstractJob : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)

public:
    explicit AbstractJob(QObject* parent = 0);

    QString name() const;

protected:
    QString m_name;
};

#endif // ABSTRACTJOB_H
