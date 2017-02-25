#include "woccapplication.h"
#include "common.h"
#include "Utilities/logger.h"

#include <QSettings>
#include <QLoggingCategory>
#include <QTime>

WoccApplication::WoccApplication(int &argc, char **argv) :
  #ifndef console_mode
    QApplication(argc, argv)
  #else
    QCoreApplication(argc, argv)
  #endif
{
#ifndef QT_NO_DEBUG_OUTPUT
    // Qt debug output is disabled on some systems, this reenables it at the project level.
    // https://bugzilla.redhat.com/show_bug.cgi?id=1227295
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
#endif

    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QCoreApplication::setOrganizationName(ORGANISATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANISATION_DOMAIN);

    qInstallMessageHandler(Logger::instance()->log);
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
}
