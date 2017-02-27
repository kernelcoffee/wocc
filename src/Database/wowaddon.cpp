#include "wowaddon.h"
#include <QDebug>

WowAddon::WowAddon(QObject *parent) :
    QObject(parent)
{
}

QString WowAddon::name() const
{
    return m_name;
}

void WowAddon::addAuthor(const QString& name, const QString& url)
{
    m_authors.append({name, url});
}

void WowAddon::addCategory(int id, const QString& name, const QString& url)
{
    m_categories.append(Category({id, name, url}));
}

uint WowAddon::installCount() const
{
    return m_installCount;
}

QString WowAddon::summary() const
{
    return m_summary;
}

void WowAddon::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void WowAddon::setInstallCount(uint installCount)
{
    if (m_installCount == installCount)
        return;

    m_installCount = installCount;
    emit installCountChanged(installCount);
}

void WowAddon::setSummary(QString summary)
{
    if (m_summary == summary)
        return;

    m_summary = summary;
    emit summaryChanged(summary);
}
