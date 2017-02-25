#ifndef WOCCAPPLICATION_H
#define WOCCAPPLICATION_H

#ifndef nox_mode
#include <QApplication>
#else
#include <QCoreApplication>
#endif

#ifndef nox_mode
class WoccApplication : public QApplication
#else
class WoccApplication : public QApplication
#endif
{
    Q_OBJECT
public:
    explicit WoccApplication(int &argc, char **argv);


};

#endif // WOCCAPPLICATION_H
