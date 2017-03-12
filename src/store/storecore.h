#ifndef STORECORE_H
#define STORECORE_H

#include "abstracts/abstractcore.h"
#include "curse/store.h"

class CoreManager;

class storeCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit storeCore(CoreManager *parent = nullptr);

    Curse::Store* curse() const;
private:
    Curse::Store* m_curse;
};

#endif // STORECORE_H
