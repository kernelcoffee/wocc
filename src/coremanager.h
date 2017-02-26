#ifndef COREMANAGER_H
#define COREMANAGER_H

#include "Abstracts/abstractcore.h"

#ifndef console_mode
#include "Ui/uicore.h"
#endif

#include "Console/consolecore.h"
#include "Network/networkcore.h"
#include "Database/databasecore.h"

#include <QObject>
#include <QList>

class CoreManager : public AbstractCore
{
    Q_OBJECT
public:
    explicit CoreManager(QObject *parent = 0);
    ~CoreManager();

    void    init();
    void    initSettings();
    void    initArguments(QCommandLineParser &parser);
    void    processArguments(QCommandLineParser &parser);

    NetworkCore* network() const;
    DatabaseCore* database() const;

public slots:
    void    delayedInit();
    void    aboutToQuit();

private:
    Q_DISABLE_COPY(CoreManager)

    QList<AbstractCore*>   m_cores;

#ifndef console_mode
    UiCore  *m_ui;
#endif

    NetworkCore *m_network;
    DatabaseCore *m_database;
    ConsoleCore *m_console;
};

#endif // COREMANAGER_H
