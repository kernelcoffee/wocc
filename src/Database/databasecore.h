#ifndef DATABASECORE_H
#define DATABASECORE_H

#include "Abstracts/abstractcore.h"

class CoreManager;
class NetworkCore;

class DatabaseCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit DatabaseCore(CoreManager *parent = 0);

    void init();
    void initSettings();

public slots:
    void aboutToQuit();

    void update();

private:
    NetworkCore *m_network = nullptr;
};

#endif // DATABASECORE_H
