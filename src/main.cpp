#include "woccapplication.h"
#include "coremanager.h"

int main(int argc, char *argv[])
{
    WoccApplication app(argc, argv);
    CoreManager cores;

    QCommandLineParser parser;

    QObject::connect(&cores, &CoreManager::initDone, [&app, &cores, &parser]() {
        parser.process(app);
        cores.processArguments(parser);
    });

    cores.init();
    cores.initSettings();
    cores.initArguments(parser);

    return app.exec();
}

