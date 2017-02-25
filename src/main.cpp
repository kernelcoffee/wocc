#include "woccapplication.h"
#include "coremanager.h"

int main(int argc, char *argv[])
{
    WoccApplication app(argc, argv);
    auto cores = CoreManager::instance();

    cores->init();
    cores->initSettings();

    return app.exec();
}

