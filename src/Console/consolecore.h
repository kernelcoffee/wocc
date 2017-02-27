#ifndef CONSOLECORE_H
#define CONSOLECORE_H

#include "Abstracts/abstractcore.h"
#include <QCommandLineOption>
#include <QMap>
#include <functional>

class CoreManager;
class DatabaseCore;

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

    QStringList m_args;
    DatabaseCore* m_database;

    QMap<QString, std::function<void ()>> m_commandMap;
};

#endif // CONSOLECORE_H
