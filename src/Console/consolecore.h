#ifndef CONSOLECORE_H
#define CONSOLECORE_H

#include "Abstracts/abstractcore.h"

class ConsoleCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit ConsoleCore(QObject *parent = 0);

    void init();
    void initSettings();
    void initArguments(QCommandLineParser &cmd);
    void processArguments(QCommandLineParser &cmd);

signals:

public slots:
    void aboutToQuit();
};

#endif // CONSOLECORE_H
