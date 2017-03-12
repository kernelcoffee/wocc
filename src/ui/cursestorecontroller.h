#ifndef CURSESTORECONTROLLER_H
#define CURSESTORECONTROLLER_H

#include <QObject>

namespace Curse {
class Store;
}

class CurseAddonModel;

class CursestoreController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString wowDir READ wowDir WRITE setWowDir NOTIFY wowDirChanged)
    Q_PROPERTY(CurseAddonModel* wowModel READ wowModel CONSTANT)
    Q_PROPERTY(CurseAddonModel* wowInstalledModel READ wowInstalledModel CONSTANT)
public:
    enum class State {
        Ready,
        Refreshing,
        Detecting
    };

    CursestoreController() {}
    explicit CursestoreController(Curse::Store* store, QObject *parent = nullptr);

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void detect();
    Q_INVOKABLE void update(int index);

    QString wowDir() const;

    CurseAddonModel* wowModel() const;
    CurseAddonModel* wowInstalledModel() const;

public slots:
    void setWowDir(const QString &wowDir);

signals:
    void wowDirChanged(const QString &wowDir);

private:
    Curse::Store* m_store;
    CurseAddonModel* m_wowModel;
    CurseAddonModel* m_wowInstalledModel;

    QString m_wowDir;
};

#endif // CURSESTORECONTROLLER_H
