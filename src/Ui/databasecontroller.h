#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include "wowaddonmodel.h"

class DatabaseCore;

class DatabaseController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString wowDir READ wowDir WRITE setWowDir NOTIFY wowDirChanged)
    Q_PROPERTY(WowAddonModel* wowModel READ wowModel CONSTANT)
    Q_PROPERTY(WowAddonModel* wowInstalledModel READ wowInstalledModel CONSTANT)
public:
    DatabaseController() {}
    explicit DatabaseController(DatabaseCore* database, QObject *parent = nullptr);

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void detect();

    QString wowDir() const;

    WowAddonModel* wowModel() const;
    WowAddonModel* wowInstalledModel() const;

public slots:
    void setWowDir(const QString &wowDir);

signals:
    void wowDirChanged(const QString &wowDir);

private:
    DatabaseCore* m_database;
    WowAddonModel* m_wowModel;
    WowAddonModel* m_wowInstalledModel;

    QString m_wowDir;
};

#endif // DATABASECONTROLLER_H
