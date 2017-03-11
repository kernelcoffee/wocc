#include "storecore.h"
#include "coremanager.h"
#include "Store/cursestore.h"

StoreCore::StoreCore(CoreManager *parent) :
    AbstractCore(parent)
  , m_curseStore(new CurseStore(parent->network()))
{

}

CurseStore*StoreCore::curseStore() const
{
    return m_curseStore;
}
