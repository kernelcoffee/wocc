#include "uicore.h"
#include "coremanager.h"
#include "Database/databasecore.h"

#include "databasecontroller.h"

#include <QQmlContext>
#include <QDebug>

UiCore::UiCore(CoreManager *parent) :
    AbstractCore(parent)
  , m_database(parent->database())
{

}

void UiCore::startX()
{
    initContext();

    m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
}

void UiCore::initContext()
{
    m_dbController = new DatabaseController(m_database);

    QQmlContext* context = m_engine.rootContext();

    qmlRegisterType<DatabaseController>("Wocc", 1, 0, "DatabaseController");

    context->setContextProperty("_database", m_dbController);
    context->setContextProperty("addonModel", m_dbController->wowModel());
}
