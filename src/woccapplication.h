#ifndef WOCCAPPLICATION_H
#define WOCCAPPLICATION_H

#ifndef nox_mode
#include <QApplication>
#else
#include <QCoreApplication>
#endif

#include <QCommandLineParser>


#ifndef nox_mode
class WoccApplication : public QApplication
#else
class WoccApplication : public QCoreApplication
#endif
{
    Q_OBJECT
public:
    explicit WoccApplication(int &argc, char **argv);
};

#endif // WOCCAPPLICATION_H
