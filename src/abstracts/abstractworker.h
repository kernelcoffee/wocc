#ifndef ABSTRACTWORKER_H
#define ABSTRACTWORKER_H

#include <QObject>

class AbstractWorker : public QObject
{
    Q_OBJECT
public:
    explicit AbstractWorker(QObject* parent = nullptr);

signals:

public slots:
};

#endif // ABSTRACTWORKER_H
