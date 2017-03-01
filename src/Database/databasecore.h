#ifndef DATABASECORE_H
#define DATABASECORE_H

#include "Abstracts/abstractcore.h"
#include "wowaddon.h"

#include <QVector>

class CoreManager;
class NetworkCore;

class DatabaseCore : public AbstractCore
{
    Q_OBJECT

public:
    explicit DatabaseCore(CoreManager *parent = nullptr);
    ~DatabaseCore();

    QVector<WowAddon*> addonList() const;

signals:
    void wowAddonListUpdated(const QVector<WowAddon*> &addonList);

public slots:
    void refresh(bool isAsync = true);
    void detect();

private slots:
    void processCurseAddonArchive();

private:
    Q_DISABLE_COPY(DatabaseCore)
    bool decompressBzip2File(const QString &filePath);

    CoreManager *m_cores = nullptr;
    NetworkCore *m_network = nullptr;
    QVector<WowAddon*> m_addonList;
    QVector<WowAddon*> m_installedList;
};

#endif // DATABASECORE_H
