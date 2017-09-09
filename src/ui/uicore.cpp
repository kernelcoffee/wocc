#include "uicore.h"
#include "coremanager.h"

#include "store/storecore.h"
#include "store/curse/store.h"
#include "store/curse/addon.h"

#include "abstracts/abstractgame.h"
#include "abstracts/abstractstore.h"
#include "abstracts/abstractjob.h"
#include "abstracts/abstractworker.h"

#include "cursestorecontroller.h"
#include "curseaddonmodel.h"

#include "store/curse/worldofwarcraft/worldofwarcraft.h"

#include <QQmlContext>
#include <QDebug>
#include <QQuickStyle>

UiCore::UiCore(CoreManager* parent) :
    AbstractCore(parent)
    , m_stores(parent->stores())
{
    QQuickStyle::setStyle("Material");
}

void UiCore::startX()
{
    initContext();

    m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (m_engine.rootObjects().isEmpty()) {
        qFatal("Could not load the main view");
    }

}

void UiCore::initContext()
{
    m_cstoreController = new CurseStoreController(m_stores->curse());

    QQmlContext* context = m_engine.rootContext();

    qmlRegisterType<AbstractGame>("Wocc", 1, 0, "AbstractGame");
    qmlRegisterType<AbstractStore>("Wocc", 1, 0, "AbstractStore");
    qmlRegisterType<AbstractJob>("Wocc", 1, 0, "AbstractJob");
    qmlRegisterType<AbstractWorker>("Wocc", 1, 0, "AbstractWorker");

    qmlRegisterType<CurseStoreController>("Wocc", 1, 0, "CurseStore");
    qmlRegisterType<Curse::WorldOfWarcraft>("Wocc", 1, 0, "WorldOfWarcraft");
    qmlRegisterType<Curse::Addon>("Wocc", 1, 0, "CurseAddon");
    qRegisterMetaType<CurseAddonModel*>("CurseAddonModel*");


    context->setContextProperty("_cursestore", m_cstoreController);
}
