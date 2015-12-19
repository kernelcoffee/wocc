#ifndef COREMANAGER_H
#define COREMANAGER_H

#include "Utilities/singleton.h"
#include "Abstracts/abstractcore.h"

#ifndef nox_mode
#include "Ui/uicore.h"
#else
#include "Console/consolecore.h"
#endif

#include <QObject>
#include <QMap>

class CoreManager : public AbstractCore, public Singleton<CoreManager>
{
    friend class Singleton<CoreManager>;

    Q_OBJECT
public:
    explicit CoreManager(QObject *parent = 0);
    ~CoreManager();

    void    init();
    void    initSettings();
    void    initArguments(QCommandLineParser &cmd);
    void    processArguments(QCommandLineParser &cmd);

signals:

public slots:
    void    delayedInit();
    void    aboutToQuit();

private:
    QMap<QString, AbstractCore*>   m_cores;
#ifndef nox_mode
    UiCore  *m_ui;
#else
    ConsoleCore *m_console;
#endif

};

#endif // COREMANAGER_H
