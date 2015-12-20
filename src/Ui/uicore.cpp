#include "uicore.h"

UiCore::UiCore(QObject *parent) :
    AbstractCore(parent)
{

}

void UiCore::init()
{
    m_engine.addImportPath("qrc:/qml-material/modules");
    m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
}

void UiCore::initSettings()
{

}

void UiCore::aboutToQuit()
{

}
