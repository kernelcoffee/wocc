#include "databasecontroller.h"
#include "Database/databasecore.h"
#include "Ui/wowaddonmodel.h"

#include <QDir>
#include <QUrl>
#include <QDebug>
#include <QSettings>
#include <QStandardPaths>

DatabaseController::DatabaseController(DatabaseCore* database, QObject* parent) :
    QObject(parent)
  , m_database(database)
  , m_wowModel(new WowAddonModel)
{
    qDebug() << database;
    QSettings settings;
    connect(m_database, &DatabaseCore::wowAddonListUpdated,
            m_wowModel, &WowAddonModel::setData);

    connect(this, &DatabaseController::wowDirChanged, [](const QString &wowDir){
        QSettings settings;
        settings.setValue("wowDir", wowDir);
    });
    setWowDir(settings.value("wowDir", QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).toString());
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

void DatabaseController::detect()
{
    QDir dir(QUrl(m_wowDir).toLocalFile() + "/Interface/AddOns");

    qDebug() << dir.absolutePath();
    if (!dir.exists()) {
        qDebug() << "path doesn't exist";
    }

    QFileInfoList entries = dir.entryInfoList( QDir::NoDotAndDotDot | QDir::Dirs);

    for (auto entry : entries) {
        qDebug() << entry.absoluteFilePath();
    }
}

QString DatabaseController::wowDir() const
{
    return m_wowDir;
}

void DatabaseController::setWowDir(const QString &wowDir)
{
    qDebug() << wowDir;

    if (m_wowDir == wowDir)
        return;

    m_wowDir = wowDir;
    emit wowDirChanged(wowDir);
}
