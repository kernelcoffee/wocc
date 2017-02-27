#ifndef UICORE_H
#define UICORE_H

#include "Abstracts/abstractcore.h"
#include <QQmlApplicationEngine>

class CoreManager;
class DatabaseController;
class DatabaseCore;


class UiCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit UiCore(CoreManager *parent = 0);

public slots:
    void startX();

private:
    void initContext();

    QQmlApplicationEngine m_engine;

    DatabaseCore* m_database = nullptr;
    DatabaseController* m_dbController = nullptr;
};

#endif // UICORE_H
