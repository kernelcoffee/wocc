#include "cursestorecontroller.h"
#include "ui/curseaddonmodel.h"
#include "store/curse/store.h"
#include "store/curse/worldofwarcraft/worldofwarcraft.h"
#include "store/curse/addon.h"

#include <QDebug>

static constexpr char settings_wowdir[] = "wowDir";

CurseStoreController::CurseStoreController(Curse::Store* store, QObject* parent) :
    QObject(parent)
    , m_store(store)
    , m_wowModel(new CurseAddonModel)
    , m_wowInstalledModel(new CurseAddonModel)
{
    connect(m_store->worldOfWarcraft(), &Curse::WorldOfWarcraft::libraryUpdated,
            m_wowModel, &CurseAddonModel::setData);
}

CurseAddonModel* CurseStoreController::wowModel() const
{
    return m_wowModel;
}

CurseAddonModel* CurseStoreController::wowInstalledModel() const
{
    return m_wowInstalledModel;
}

Curse::WorldOfWarcraft* CurseStoreController::worldOfWarcraft() const
{
    return m_store->worldOfWarcraft();
}

AbstractWorker* CurseStoreController::refresh()
{
    return m_store->refresh();
}
