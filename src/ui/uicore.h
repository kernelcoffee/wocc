#ifndef UICORE_H
#define UICORE_H

#include "abstracts/abstractcore.h"
#include <QQmlApplicationEngine>

class CoreManager;
class CurseStoreController;
class storeCore;


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

    storeCore* m_stores = nullptr;
    CurseStoreController* m_cstoreController = nullptr;
};

#endif // UICORE_H
