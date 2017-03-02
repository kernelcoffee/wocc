#ifndef CURSESTORECONTROLLER_H
#define CURSESTORECONTROLLER_H

#include <QObject>

class CurseStore;
class WowAddonModel;

class CurseStoreController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString wowDir READ wowDir WRITE setWowDir NOTIFY wowDirChanged)
    Q_PROPERTY(WowAddonModel* wowModel READ wowModel CONSTANT)
    Q_PROPERTY(WowAddonModel* wowInstalledModel READ wowInstalledModel CONSTANT)
public:
    enum class State {
        Ready,
        Refreshing,
        Detecting
    };

    CurseStoreController() {}
    explicit CurseStoreController(CurseStore* store, QObject *parent = nullptr);

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
    CurseStore* m_store;
    WowAddonModel* m_wowModel;
    WowAddonModel* m_wowInstalledModel;

    QString m_wowDir;
};

#endif // CURSESTORECONTROLLER_H
