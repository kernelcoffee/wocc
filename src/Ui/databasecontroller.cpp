#include "databasecontroller.h"
#include "Database/databasecore.h"
#include "Ui/wowaddonmodel.h"

#include <QDebug>

DatabaseController::DatabaseController(DatabaseCore* database, QObject* parent) :
    QObject(parent)
  , m_database(database)
  , m_wowModel(new WowAddonModel)
{
    qDebug() << database;
    connect(m_database, &DatabaseCore::wowAddonListUpdated,
            m_wowModel, &WowAddonModel::setData);
}

WowAddonModel* DatabaseController::wowModel() const
{
    qDebug() << m_wowModel;
    return m_wowModel;
}

void DatabaseController::refresh()
{
    m_database->update();
}
