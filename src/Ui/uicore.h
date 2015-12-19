#ifndef UICORE_H
#define UICORE_H

#include "Abstracts/abstractcore.h"
#include <QQmlApplicationEngine>

class UiCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit UiCore(QObject *parent = 0);
    void init();
    void initSettings();

signals:

public slots:
    void aboutToQuit();

private:
    QQmlApplicationEngine m_engine;
};

#endif // UICORE_H
