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
    void update(bool isAsync = true);

private:
    Q_DISABLE_COPY(DatabaseCore)
    bool inflate(const QString filePath);

    CoreManager *m_cores = nullptr;
    NetworkCore *m_network = nullptr;
    QVector<WowAddon*> m_database;
};

#endif // DATABASECORE_H
