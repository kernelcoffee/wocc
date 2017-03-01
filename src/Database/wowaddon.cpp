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

QString WowAddon::shortName() const
{
    return m_shortName;
}

void WowAddon::addAuthor(const QString& name, const QString& url)
{
    m_authors.append(Author({name, url}));
}

void WowAddon::addCategory(int id, const QString& name, const QString& url)
{
    m_categories.append(Category({id, name, url}));
}

void WowAddon::addFolder(const QString &name, const QString &fingerprint)
{
    m_folders.append({name, fingerprint});
}

QList<WowAddon::Author> WowAddon::authors() const
{
    return m_authors;
}

QList<WowAddon::Folder> WowAddon::folders() const
{
    return m_folders;
}

QUrl WowAddon::downloadUrl() const
{
    return m_downloadUrl;
}

QUrl WowAddon::websiteUrl() const
{
    return m_websiteUrl;
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
    m_id = id;
}

void WowAddon::setName(const QString &name)
{
    m_name = name;
}

void WowAddon::setInstallCount(uint installCount)
{
    m_installCount = installCount;
}

void WowAddon::setDownloadUrl(const QString &downloadUrl)
{
    m_downloadUrl = QUrl(downloadUrl);
}

void WowAddon::setWebsiteUrl(const QString &websiteUrl)
{
    m_shortName = websiteUrl.section('/', -1);
    m_downloadUrl = QUrl(websiteUrl);
}

void WowAddon::setSummary(const QString &summary)
{
    m_summary = summary;
}
