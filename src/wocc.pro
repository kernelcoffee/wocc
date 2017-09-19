QT += core network

CONFIG += c++14

lessThan(QT_VERSION, 5.7.0) {
    error("requires at least Qt 5.7")
}

TEMPLATE = app
TARGET = wocc

LIBS += -lz -lquazip5

CONFIG(console_mode) {
    QT -= gui

    CONFIG += console
    CONFIG -= app_bundle


    DEFINES += console_mode

    message(console_mode enabled)
} else {
    QT += qml quick widgets quickcontrols2

    RESOURCES += \
            ressources/qml/qml.qrc

    # Default rules for deployment.
    include(deployment.pri)
    message(ui mode enabled)

HEADERS += \
    ui/uicore.h \
    ui/curseaddonmodel.h \
    ui/cursestorecontroller.h \

SOURCES += \
    ui/uicore.cpp \
    ui/curseaddonmodel.cpp \
    ui/cursestorecontroller.cpp \
}

HEADERS += \
    common.h \
    coremanager.h \
    utilities/logger.h \
    utilities/singleton.h \
    abstracts/abstractcore.h \
    woccapplication.h \
    network/networkcore.h \
    network/filedownloader.h \
    console/consolecore.h \
    utilities/fileextractor.h \
    store/storecore.h \
    abstracts/abstractaddon.h \
    abstracts/abstractgame.h \
    store/curse/xmlparser.h \
    store/curse/worldofwarcraft/worldofwarcraft.h \
    store/curse/addon.h \
    store/curse/store.h \
    threads/threadcore.h \
    store/curse/downloadfilejob.h \
    abstracts/abstractstore.h \
    abstracts/abstracttask.h \
    store/curse/refreshlibrarytask.h \
    store/curse/worldofwarcraft/installtask.h \
    store/curse/worldofwarcraft/detecttask.h

SOURCES += main.cpp \
    coremanager.cpp \
    utilities/logger.cpp \
    abstracts/abstractcore.cpp \
    woccapplication.cpp \
    network/networkcore.cpp \
    network/filedownloader.cpp \
    console/consolecore.cpp \
    utilities/fileextractor.cpp \
    store/storecore.cpp \
    abstracts/abstractaddon.cpp \
    abstracts/abstractgame.cpp \
    store/curse/xmlparser.cpp \
    store/curse/worldofwarcraft/worldofwarcraft.cpp \
    store/curse/addon.cpp \
    store/curse/store.cpp \
    threads/threadcore.cpp \
    store/curse/downloadfilejob.cpp \
    abstracts/abstractstore.cpp \
    abstracts/abstracttask.cpp \
    store/curse/refreshlibrarytask.cpp \
    store/curse/worldofwarcraft/installtask.cpp \
    store/curse/worldofwarcraft/detecttask.cpp

DISTFILES += style.astylerc
