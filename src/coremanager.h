#ifndef COREMANAGER_H
#define COREMANAGER_H

#include "abstracts/abstractcore.h"

#include <QObject>
#include <QList>

class ConsoleCore;
class NetworkCore;
class ThreadCore;
class storeCore;

#ifndef console_mode
class UiCore;
#endif

class CoreManager : public AbstractCore
{
    Q_OBJECT
public:
    explicit CoreManager(QObject* parent = 0);
    ~CoreManager();

    void init();
    void initSettings();
    void initArguments(QCommandLineParser& parser);
    void processArguments(QCommandLineParser& parser);

    bool consoleMode();

    NetworkCore* network() const;
    storeCore* stores() const;

public slots:
    void delayedInit();
    void aboutToQuit();
    void setConsoleMode(bool consoleMode);

private:
    Q_DISABLE_COPY(CoreManager)

    QList<AbstractCore*> m_cores;

    bool m_consoleMode = false;

#ifndef console_mode
    UiCore* m_ui = nullptr;
#endif

    NetworkCore* m_network = nullptr;
    ThreadCore* m_threads = nullptr;
    ConsoleCore* m_console = nullptr;
    storeCore* m_stores = nullptr;
};

#endif // COREMANAGER_H
