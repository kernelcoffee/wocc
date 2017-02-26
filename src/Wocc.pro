QT += core network

CONFIG += c++11

lessThan(QT_VERSION, 5.7) {
    error("requires at least Qt 5.7")
}

TEMPLATE = app
TARGET = wocc

CONFIG(console_mode) {
    QT -= gui

    CONFIG += console
    CONFIG -= app_bundle


    DEFINES += console_mode

    message(console_mode enabled)
} else {
    QT += qml quick widgets

    RESOURCES += \
            Ressources/Qml/qml.qrc

    # Default rules for deployment.
    include(deployment.pri)
    message(ui mode enabled)

HEADERS += \
    Ui/uicore.h \

SOURCES += \
    Ui/uicore.cpp \
}

HEADERS += \
    common.h \
    coremanager.h \
    Utilities/logger.h \
    Utilities/singleton.h \
    Abstracts/abstractcore.h \
    woccapplication.h \
    Network/networkcore.h \
    Network/filedownloader.h \
    Database/databasecore.h \
    Console/consolecore.h \

SOURCES += main.cpp \
    coremanager.cpp \
    Utilities/logger.cpp \
    Abstracts/abstractcore.cpp \
    woccapplication.cpp \
    Network/networkcore.cpp \
    Network/filedownloader.cpp \
    Database/databasecore.cpp \
    Console/consolecore.cpp \
