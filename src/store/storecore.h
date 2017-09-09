#ifndef STORECORE_H
#define STORECORE_H

#include "abstracts/abstractcore.h"
#include "curse/store.h"

class CoreManager;

class storeCore : public AbstractCore
{
    Q_PROPERTY(AbstractStore* curse READ curse CONSTANT)

    Q_OBJECT
public:
    explicit storeCore(CoreManager* parent = nullptr);

    virtual void init() override;

    Curse::Store* curse() const;
private:
    CoreManager* m_cores;
    Curse::Store* m_curse;
};

#endif // STORECORE_H
