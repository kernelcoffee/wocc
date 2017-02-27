#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include "wowaddonmodel.h"

class DatabaseCore;

class DatabaseController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(WowAddonModel* wowModel READ wowModel CONSTANT)
public:
    DatabaseController() {}
    explicit DatabaseController(DatabaseCore* database, QObject *parent = nullptr);

    WowAddonModel* wowModel() const;

    Q_INVOKABLE void refresh();

private:
    DatabaseCore* m_database;
    WowAddonModel* m_wowModel;

};

#endif // DATABASECONTROLLER_H
