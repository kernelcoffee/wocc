#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include "wowaddonmodel.h"

class DatabaseCore;

class DatabaseController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(WowAddonModel* wowModel READ wowModel CONSTANT)
    Q_PROPERTY(QString wowDir READ wowDir WRITE setWowDir NOTIFY wowDirChanged)
public:
    DatabaseController() {}
    explicit DatabaseController(DatabaseCore* database, QObject *parent = nullptr);

    WowAddonModel* wowModel() const;
    QString wowDir() const;

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void detect();

public slots:
    void setWowDir(const QString &wowDir);

signals:
    void wowDirChanged(const QString &wowDir);

private:
    DatabaseCore* m_database;
    WowAddonModel* m_wowModel;

    QString m_wowDir;
};

#endif // DATABASECONTROLLER_H
