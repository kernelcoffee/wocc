#ifndef WORLDOFWARCRAFT_H
#define WORLDOFWARCRAFT_H

#include <QObject>

class WorldOfWarcraft : public QObject
{
    Q_OBJECT
public:
    explicit WorldOfWarcraft(QObject *parent = 0);

signals:

public slots:
};

#endif // WORLDOFWARCRAFT_H