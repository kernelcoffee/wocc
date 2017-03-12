#include "cursestorecontroller.h"
#include "ui/curseaddonmodel.h"
#include "store/curse/store.h"
#include "store/curse/worldofwarcraft/worldofwarcraft.h"
#include "store/curse/addon.h"

#include <QDebug>
#include <QSettings>
#include <QStandardPaths>

static constexpr char settings_wowdir[] = "wowDir";

CursestoreController::CursestoreController(Curse::Store* store, QObject* parent) :
    QObject(parent)
  , m_store(store)
  , m_wowModel(new CurseAddonModel)
  , m_wowInstalledModel(new CurseAddonModel)
{
    QSettings settings;

    connect(this, &CursestoreController::wowDirChanged, [&settings](const QString &wowDir){
        settings.setValue(settings_wowdir, wowDir);
    });

    setWowDir(settings.value(settings_wowdir, QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).toString());

    connect(m_store->wow(), &Curse::WorldOfWarcraft::libraryUpdated,
            m_wowModel, &CurseAddonModel::setData);
//    connect(m_store, &Curse::Store::wowInstalledListUpdated,
//            m_wowInstalledModel, &WowAddonModel::setData);

//    m_store->loadLibraries();
//    m_store->loadInstalled();
}

void CursestoreController::refresh()
{
    m_store->wow()->refresh();
}

void CursestoreController::detect()
{
//    m_store->detect();
}

void CursestoreController::update(int index)
{
    Q_UNUSED(index)
//    m_store->update(m_store->wowLibrary().at(index));
}

QString CursestoreController::wowDir() const
{
    return m_wowDir;
}

CurseAddonModel* CursestoreController::wowModel() const
{
    return m_wowModel;
}

CurseAddonModel *CursestoreController::wowInstalledModel() const
{
    return m_wowInstalledModel;
}

void CursestoreController::setWowDir(const QString &wowDir)
{
    if (m_wowDir == wowDir)
        return;

    m_wowDir = wowDir;
    emit wowDirChanged(wowDir);
}
