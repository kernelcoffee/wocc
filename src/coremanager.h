#ifndef COREMANAGER_H
#define COREMANAGER_H

#include "Abstracts/abstractcore.h"


#include "Console/consolecore.h"
#include "Network/networkcore.h"
#include "Database/databasecore.h"

#ifndef console_mode
#include "Ui/uicore.h"
#endif

#include <QObject>
#include <QList>

class CoreManager : public AbstractCore
{
    Q_OBJECT
public:
    explicit CoreManager(QObject *parent = 0);
    ~CoreManager();

    void init();
    void initSettings();
    void initArguments(QCommandLineParser &parser);
    void processArguments(QCommandLineParser &parser);

    bool consoleMode();

    NetworkCore* network() const;
    DatabaseCore* database() const;

public slots:
    void delayedInit();
    void aboutToQuit();
    void setConsoleMode(bool consoleMode);

private:
    Q_DISABLE_COPY(CoreManager)

    QList<AbstractCore*> m_cores;

    bool m_consoleMode = false;

#ifndef console_mode
    UiCore *m_ui = nullptr;
#endif

    NetworkCore *m_network = nullptr;
    DatabaseCore *m_database = nullptr;
    ConsoleCore *m_console = nullptr;
};

#endif // COREMANAGER_H
