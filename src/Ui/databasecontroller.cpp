#include "databasecontroller.h"
#include "Database/databasecore.h"
#include "Ui/wowaddonmodel.h"

#include <QDebug>
#include <QSettings>
#include <QStandardPaths>

static constexpr char settings_wowdir[] = "wowDir";

DatabaseController::DatabaseController(DatabaseCore* database, QObject* parent) :
    QObject(parent)
  , m_database(database)
  , m_wowModel(new WowAddonModel)
  , m_wowInstalledModel(new WowAddonModel)
{
    QSettings settings;

    connect(this, &DatabaseController::wowDirChanged, [&settings](const QString &wowDir){
        settings.setValue(settings_wowdir, wowDir);
    });

    setWowDir(settings.value(settings_wowdir, QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).toString());

    connect(m_database, &DatabaseCore::wowAddonListUpdated,
            m_wowModel, &WowAddonModel::setData);
    connect(m_database, &DatabaseCore::wowInstalledAddonListUpdated,
            m_wowInstalledModel, &WowAddonModel::setData);
}

void DatabaseController::refresh()
{
    m_database->refresh();
}

void DatabaseController::detect()
{
    m_database->detect();
}

QString DatabaseController::wowDir() const
{
    return m_wowDir;
}

WowAddonModel* DatabaseController::wowModel() const
{
    qDebug() << m_wowModel;
    return m_wowModel;
}

WowAddonModel *DatabaseController::wowInstalledModel() const
{
    qDebug() << m_wowInstalledModel;
    return m_wowInstalledModel;
}

void DatabaseController::setWowDir(const QString &wowDir)
{
    qDebug() << wowDir;

    if (m_wowDir == wowDir)
        return;

    m_wowDir = wowDir;
    emit wowDirChanged(wowDir);
}
