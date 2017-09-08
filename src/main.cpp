#include "woccapplication.h"
#include "coremanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    WoccApplication app(argc, argv);
    CoreManager cores;

    QCommandLineParser parser;

    cores.init();
    cores.initSettings();
    cores.initArguments(parser);
    parser.process(app);
    cores.processArguments(parser);

    return app.exec();
}
