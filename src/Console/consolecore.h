#ifndef CONSOLECORE_H
#define CONSOLECORE_H

#include "Abstracts/abstractcore.h"
#include <QCommandLineOption>
#include <QMap>
#include <functional>

class CoreManager;
class StoreCore;

class ConsoleCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit ConsoleCore(CoreManager *parent = nullptr);

    void init();
    void initArguments(QCommandLineParser &parser);
    void processArguments(QCommandLineParser &parser);

signals:
    void noCommandToProcess();
    void databaseUpdated();

public slots:
    void delayedInit();

private:
    Q_DISABLE_COPY(ConsoleCore)

    void update();
    void detect();

    QStringList m_args;

    CoreManager* m_cores = nullptr;
    StoreCore* m_stores = nullptr;

    QMap<QString, std::function<void ()>> m_commandMap;
};

#endif // CONSOLECORE_H
