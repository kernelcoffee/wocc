#ifndef CONSOLECORE_H
#define CONSOLECORE_H

#include "Abstracts/abstractcore.h"
#include <QCommandLineOption>

class CoreManager;
class DatabaseCore;

class ConsoleCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit ConsoleCore(CoreManager *parent = nullptr);

    void initArguments(QCommandLineParser &parser);
    void processArguments(QCommandLineParser &parser);

signals:
    void noCommandToProcess();
    void databaseUpdated();

public slots:
    void aboutToQuit();
    void delayedInit();

private:
    Q_DISABLE_COPY(ConsoleCore)

    QStringList m_args;
    DatabaseCore* m_database;
};

#endif // CONSOLECORE_H
