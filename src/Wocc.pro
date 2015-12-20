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
            qml.qrc

    # Additional import path used to resolve QML modules in Qt Creator's code model
    include(lib/qml-material-qrc/qml-material-qrc.pri)
    QML_IMPORT_PATH += $$PWD/lib/qml-material-qrc/qml-material/modules

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

SOURCES += main.cpp \
    coremanager.cpp \
    Utilities/logger.cpp \
    Abstracts/abstractcore.cpp \

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
