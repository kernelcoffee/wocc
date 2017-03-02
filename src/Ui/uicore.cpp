#include "uicore.h"
#include "coremanager.h"
#include "Store/storecore.h"
#include "wowaddonmodel.h"

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
    m_cStoreController = new CurseStoreController(m_stores->curseStore());

    QQmlContext* context = m_engine.rootContext();

    qmlRegisterType<CurseStoreController>("Wocc", 1, 0, "CurseStoreController");
    qRegisterMetaType<WowAddonModel*>("WowAddonModel*");

    context->setContextProperty("_curseStore", m_cStoreController);
}
