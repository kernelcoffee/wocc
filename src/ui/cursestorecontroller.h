#ifndef CURSESTORECONTROLLER_H
#define CURSESTORECONTROLLER_H

#include <store/curse/store.h>

using namespace Curse;

class CurseAddonModel;
class WorldOfWarcraft;
class AbstractTask;

class CurseStoreController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(CurseAddonModel* wowModel READ wowModel CONSTANT)
    Q_PROPERTY(CurseAddonModel* wowInstalledModel READ wowInstalledModel CONSTANT)
    Q_PROPERTY(CurseAddonModel* dependencyModel READ dependencyModel NOTIFY dependencyModelChanged)
    Q_PROPERTY(Curse::WorldOfWarcraft* worldOfWarcraft READ worldOfWarcraft CONSTANT)

public:
    CurseStoreController() {}
    explicit CurseStoreController(Curse::Store* store, QObject* parent = nullptr);

    CurseAddonModel* wowModel() const;
    CurseAddonModel* wowInstalledModel() const;
    CurseAddonModel* dependencyModel();

    Curse::WorldOfWarcraft* worldOfWarcraft() const;

    Q_INVOKABLE AbstractTask* refresh();
    Q_INVOKABLE void setDependencyModel(Curse::Addon* addon, int game);

signals:
    void dependencyModelChanged(CurseAddonModel* model);

private:
    Curse::Store* m_store = nullptr;
    CurseAddonModel* m_wowModel = nullptr;
    CurseAddonModel* m_wowInstalledModel = nullptr;
    CurseAddonModel* m_dependencyModel = nullptr;
    Curse::WorldOfWarcraft* m_worldOfWarcraft = nullptr;
};

#endif // CURSESTORECONTROLLER_H
