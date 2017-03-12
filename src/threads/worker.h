#ifndef WORKER_H
#define WORKER_H

#include <QThread>

class Worker : public QThread
{
    Q_OBJECT
public:
    enum class Status {
        Idle,
        Running
    };

    explicit Worker(QObject *parent = 0);

signals:

public slots:

private:
    Status m_status = Status::Idle;
};

#endif // WORKER_H
