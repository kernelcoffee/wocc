#ifndef STORECORE_H
#define STORECORE_H

#include "Abstracts/abstractcore.h"

class CoreManager;
class CurseStore;

class StoreCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit StoreCore(CoreManager *parent = nullptr);

    CurseStore* curseStore() const;
private:
    CurseStore* m_curseStore;
};

#endif // STORECORE_H
