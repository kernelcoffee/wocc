#ifndef ABSTRACTADDON_H
#define ABSTRACTADDON_H

#include <QObject>

class AbstractAddon : public QObject
{
    Q_OBJECT
public:
    explicit AbstractAddon(QObject *parent = 0);

signals:

public slots:
};

#endif // ABSTRACTADDON_H