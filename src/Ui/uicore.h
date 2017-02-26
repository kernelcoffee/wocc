#ifndef UICORE_H
#define UICORE_H

#include "Abstracts/abstractcore.h"
#include <QQmlApplicationEngine>

class UiCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit UiCore(QObject *parent = 0);

public slots:
    void startX();

private:
    QQmlApplicationEngine m_engine;
};

#endif // UICORE_H
