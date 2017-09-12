#include "storecore.h"
#include "coremanager.h"
#include "store/curse/store.h"

storeCore::storeCore(CoreManager* parent) :
    AbstractCore(parent)
    , m_cores(parent)
    , m_curse(new Curse::Store())
{
}

void storeCore::init()
{
    m_curse->init(m_cores->network(), m_cores->threads());
}

void storeCore::delayedInit()
{
    m_curse->refresh();
}

Curse::Store* storeCore::curse() const
{
    return m_curse;
}
