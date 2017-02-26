#include "uicore.h"
#include <QDebug>

UiCore::UiCore(QObject *parent) :
    AbstractCore(parent)
{

}

void UiCore::startX()
{
    m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
}
