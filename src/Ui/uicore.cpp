#include "uicore.h"
#include "coremanager.h"
#include "Database/databasecore.h"

#include "databasecontroller.h"

#include <QQmlContext>
#include <QDebug>

UiCore::UiCore(CoreManager *parent) :
    AbstractCore(parent)
  , m_database(parent->database())
  , m_dbController(new DatabaseController(parent->database()))
{

}

void UiCore::startX()
{
    initContext();

    m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
}

void UiCore::initContext()
{
    QQmlContext* context = m_engine.rootContext();
    context->setContextProperty("db", m_dbController);
}
