#ifndef CONSOLECORE_H
#define CONSOLECORE_H

#include "Abstracts/abstractcore.h"
#include <QCommandLineOption>

class ConsoleCore : public AbstractCore
{
    Q_OBJECT
public:
    explicit ConsoleCore(AbstractCore *parent = nullptr);

    void init();
    void initSettings();
    void initArguments(QCommandLineParser &parser);
    void processArguments(QCommandLineParser &parser);

public slots:
    void aboutToQuit();
};

#endif // CONSOLECORE_H
