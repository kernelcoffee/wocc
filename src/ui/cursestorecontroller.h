#ifndef CURSESTORECONTROLLER_H
#define CURSESTORECONTROLLER_H

#include <store/curse/store.h>

using namespace Curse;

class CurseAddonModel;
class WorldOfWarcraft;
class AbstractWorker;

class CurseStoreController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(CurseAddonModel* wowModel READ wowModel CONSTANT)
    Q_PROPERTY(CurseAddonModel* wowInstalledModel READ wowInstalledModel CONSTANT)
    Q_PROPERTY(Curse::WorldOfWarcraft* worldOfWarcraft READ worldOfWarcraft CONSTANT)

public:
    CurseStoreController() {}
    explicit CurseStoreController(Curse::Store* store, QObject *parent = nullptr);

    CurseAddonModel* wowModel() const;
    CurseAddonModel* wowInstalledModel() const;

    Curse::WorldOfWarcraft* worldOfWarcraft() const;

    Q_INVOKABLE AbstractWorker* refresh();

private:
    Curse::Store* m_store;
    CurseAddonModel* m_wowModel;
    CurseAddonModel* m_wowInstalledModel;
    Curse::WorldOfWarcraft* m_worldOfWarcraft;
};

#endif // CURSESTORECONTROLLER_H
