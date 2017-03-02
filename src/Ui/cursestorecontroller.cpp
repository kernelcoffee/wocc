#include "cursestorecontroller.h"
#include "Ui/wowaddonmodel.h"
#include "Store/cursestore.h"
#include "Store/wowaddon.h"

#include <QDebug>
#include <QSettings>
#include <QStandardPaths>

static constexpr char settings_wowdir[] = "wowDir";

CurseStoreController::CurseStoreController(CurseStore* store, QObject* parent) :
    QObject(parent)
  , m_store(store)
  , m_wowModel(new WowAddonModel)
  , m_wowInstalledModel(new WowAddonModel)
{
    QSettings settings;

    connect(this, &CurseStoreController::wowDirChanged, [&settings](const QString &wowDir){
        settings.setValue(settings_wowdir, wowDir);
    });

    setWowDir(settings.value(settings_wowdir, QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).toString());

    connect(m_store, &CurseStore::wowLibraryUpdated,
            m_wowModel, &WowAddonModel::setData);
    connect(m_store, &CurseStore::wowInstalledListUpdated,
            m_wowInstalledModel, &WowAddonModel::setData);

    m_store->loadLibrary();
    m_store->loadInstalled();
}

void CurseStoreController::refresh()
{
    m_store->refresh();
}

void CurseStoreController::detect()
{
    m_store->detect();
}

QString CurseStoreController::wowDir() const
{
    return m_wowDir;
}

WowAddonModel* CurseStoreController::wowModel() const
{
    return m_wowModel;
}

WowAddonModel *CurseStoreController::wowInstalledModel() const
{
    return m_wowInstalledModel;
}

void CurseStoreController::setWowDir(const QString &wowDir)
{
    if (m_wowDir == wowDir)
        return;

    m_wowDir = wowDir;
    emit wowDirChanged(wowDir);
}
