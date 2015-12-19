#include "uicore.h"

UiCore::UiCore(QObject *parent) :
    AbstractCore(parent)
{

}

void UiCore::init()
{
    m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    m_engine.addImportPath("third/qml-material/modules/");
}

void UiCore::initSettings()
{

}

void UiCore::aboutToQuit()
{

}
