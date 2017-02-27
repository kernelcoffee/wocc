#include "wowaddon.h"
#include <QDebug>

WowAddon::WowAddon(QObject *parent) :
    QObject(parent)
{
}

uint WowAddon::id() const
{
    return m_id;
}

QString WowAddon::name() const
{
    return m_name;
}

void WowAddon::addAuthor(const QString& name, const QString& url)
{
    qDebug() << name << url;
    m_authors.append(Author({name, url}));
}

void WowAddon::addCategory(int id, const QString& name, const QString& url)
{
    qDebug() << id << name << url;
    m_categories.append(Category({id, name, url}));
}

QList<WowAddon::Author> WowAddon::authors() const
{
    return m_authors;
}

uint WowAddon::installCount() const
{
    return m_installCount;
}

QString WowAddon::summary() const
{
    return m_summary;
}

void WowAddon::setId(uint id)
{
    qDebug() << id;
    m_id = id;
}

void WowAddon::setName(const QString &name)
{
    qDebug() << name;
    m_name = name;
}

void WowAddon::setInstallCount(uint installCount)
{
    qDebug() << installCount;
    m_installCount = installCount;
}

void WowAddon::setSummary(const QString &summary)
{
    qDebug() << summary;
    m_summary = summary;
}
