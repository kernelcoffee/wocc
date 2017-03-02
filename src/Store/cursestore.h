#ifndef CURSESTORE_H
#define CURSESTORE_H

#include <QObject>
#include <QVector>

class WowAddon;
class NetworkCore;

class CurseStore : public QObject
{
    Q_OBJECT
public:
    explicit CurseStore(NetworkCore* network, QObject *parent = nullptr);
    ~CurseStore();

    QVector<WowAddon*> wowLibrary() const;

signals:
    void wowLibraryUpdated(const QVector<WowAddon*> &addonList);
    void wowInstalledListUpdated(const QVector<WowAddon*> &installedAddonList);

public slots:
    void refresh(bool isAsync = true);
    void detect();

private slots:
    void processWowArchive();

private:
    QVector<WowAddon*> m_wowLibrary;
    QVector<WowAddon*> m_wowInstalled;

    NetworkCore* m_network;
};

#endif // CURSESTORE_H
