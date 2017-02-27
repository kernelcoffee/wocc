#ifndef DATABASECORE_H
#define DATABASECORE_H

#include "Abstracts/abstractcore.h"

class CoreManager;
class NetworkCore;

class DatabaseCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit DatabaseCore(CoreManager *parent = nullptr);

public slots:
    void update(bool isAsync = true);

private:
    Q_DISABLE_COPY(DatabaseCore)
    bool inflate(const QString filePath);

    NetworkCore *m_network = nullptr;
};

#endif // DATABASECORE_H
