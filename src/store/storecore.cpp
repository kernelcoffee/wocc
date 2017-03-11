#include "storecore.h"
#include "coremanager.h"
#include "store/curse/store.h"

storeCore::storeCore(CoreManager *parent) :
    AbstractCore(parent)
  , m_curse(new Curse::Store(parent->network()))
{

}

Curse::Store* storeCore::curse() const
{
    return m_curse;
}
