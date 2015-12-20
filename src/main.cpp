#include "Utilities/logger.h"
#include "coremanager.h"

#ifndef nox_mode
#include <QApplication>
#else
#include <QCoreApplication>
#endif

#include <QLoggingCategory>
#include <QSettings>
#include <QTranslator>
#include <QTimer>
#include <QTime>

int main(int argc, char *argv[])
{
#ifndef nox_mode
    QApplication app(argc, argv);
#else
    QCoreApplication app(argc, argv);
#endif

#ifndef QT_NO_DEBUG_OUTPUT
    // Qt debug output is disabled on some systems, this reenables it at the project level.
    // https://bugzilla.redhat.com/show_bug.cgi?id=1227295
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
#endif
    qInstallMessageHandler(Logger::instance()->log);
    qsrand((uint)QTime::currentTime().msec());

//    QCoreApplication::setOrganizationName("Wocc");
//    QCoreApplication::setOrganizationDomain("Wocc.org");
    QCoreApplication::setApplicationName("Wocc");

    auto cores = CoreManager::instance();

#ifndef nox_mode
    QTimer::singleShot(1, cores, SLOT(delayedInit()));
#endif

    cores->init();
    cores->initSettings();

    return app.exec();
}

