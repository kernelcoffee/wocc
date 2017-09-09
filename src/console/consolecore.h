#ifndef CONSOLECORE_H
#define CONSOLECORE_H

#include "abstracts/abstractcore.h"
#include <QCommandLineOption>
#include <QMap>
#include <functional>

class CoreManager;
class storeCore;

namespace Curse {
class Addon;
}

class ConsoleCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit ConsoleCore(CoreManager* parent = nullptr);

    virtual void init() override;
    virtual void initArguments(QCommandLineParser& parser) override;
    virtual void processArguments(QCommandLineParser& parser) override;

signals:
    void noCommandToProcess();
    void databaseUpdated();

public slots:
    virtual void delayedInit() override;

private:
    Q_DISABLE_COPY(ConsoleCore)

    void update();
    void detect();

    QStringList m_args;

    CoreManager* m_cores = nullptr;
    storeCore* m_stores = nullptr;

    QMap<QString, std::function<void ()>> m_commandMap;
};

#endif // CONSOLECORE_H
