#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>

class DatabaseCore;
class WowAddonModel;

class DatabaseController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(WowAddonModel wowModel READ wowModel NOTIFY wowModelChanged)
public:
    explicit DatabaseController(DatabaseCore* database, QObject *parent = nullptr);

    WowAddonModel* wowModel() const;

    Q_INVOKABLE void refresh();
signals:
    void wowModelChanged(WowAddonModel* wowModel);

private:
    Q_DISABLE_COPY(DatabaseController)

    DatabaseCore* m_database;
    WowAddonModel* m_wowModel;

};

#endif // DATABASECONTROLLER_H
