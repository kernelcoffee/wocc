QT += core

CONFIG += c++11

lessThan(QT_VERSION, 5.5) {
    error("requires at least Qt 5.5")
}

TEMPLATE = app

CONFIG(nox_mode) {
    QT -= gui

    CONFIG += console
    CONFIG -= app_bundle

    TARGET = wocc

    DEFINES += nox_mode

    message(nox_mode enabled)
} else {
    QT += qml quick widgets

    RESOURCES += \
            Ressources/Qml/qml.qrc

    # Default rules for deployment.
    include(deployment.pri)
    message(ui mode enabled)
}

HEADERS += \
    common.h \
    coremanager.h \
    Utilities/logger.h \
    Utilities/singleton.h \
    Abstracts/abstractcore.h \
    woccapplication.h

SOURCES += main.cpp \
    coremanager.cpp \
    Utilities/logger.cpp \
    Abstracts/abstractcore.cpp \
    woccapplication.cpp

CONFIG(nox_mode) {
HEADERS += \
    Console/consolecore.h

SOURCES += \
    Console/consolecore.cpp
} else {
HEADERS += \
    Ui/uicore.h \

SOURCES += \
    Ui/uicore.cpp \
}
