#ifndef UICORE_H
#define UICORE_H

#include "Abstracts/abstractcore.h"
#include <QQmlApplicationEngine>

class CoreManager;
class CurseStoreController;
class StoreCore;


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

    StoreCore* m_stores = nullptr;
    CurseStoreController* m_cStoreController = nullptr;
};

#endif // UICORE_H
