#include "uicore.h"
#include "coremanager.h"
#include "store/storecore.h"
#include "curseaddonmodel.h"

#include "cursestorecontroller.h"

#include <QQmlContext>
#include <QDebug>

UiCore::UiCore(CoreManager *parent) :
    AbstractCore(parent)
  , m_stores(parent->stores())
{
}

void UiCore::startX()
{
    initContext();

    m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
}

void UiCore::initContext()
{
    m_cstoreController = new CursestoreController(m_stores->curse());

    QQmlContext* context = m_engine.rootContext();

    qmlRegisterType<CursestoreController>("Wocc", 1, 0, "CursestoreController");
    qRegisterMetaType<CurseAddonModel*>("CurseAddonModel*");

    context->setContextProperty("_cursestore", m_cstoreController);
}
