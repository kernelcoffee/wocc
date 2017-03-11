#include "wowaddon.h"
#include <QDebug>

WowAddon::WowAddon(QObject *parent) :
    QObject(parent)
{
}

void WowAddon::addAuthor(const QString& name, const QString& url)
{
    m_authors.append(Author({name, url}));
}

void WowAddon::addCategory(int id, const QString& name, const QString& url)
{
    m_categories.append(Category({id, name, url}));
}

void WowAddon::printContent()
{
    qDebug() << m_name << m_shortName;
    for (auto file : m_files) {
        qDebug() << "Files" << file.name << file.downloadUrl;
        for (auto module : file.modules) {
            qDebug() << module.folderName;
        }
        qDebug();
    }
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

bool WowAddon::isInstalled() const
{
    return m_isInstalled;
}

QString WowAddon::versionInstalled() const
{
    return m_versionInstalled;
}

QString WowAddon::versionAvailable() const
{
    return m_files.first().version;
}

QString WowAddon::summary() const
{
    return m_summary;
}

uint WowAddon::installCount() const
{
    return m_installCount;
}

QList<WowAddon::Author> WowAddon::authors() const
{
    return m_authors;
}

QList<WowAddon::File> WowAddon::files()
{
    return m_files;
}

QUrl WowAddon::websiteUrl() const
{
    return m_websiteUrl;
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

void WowAddon::setWebsiteUrl(const QString &websiteUrl)
{
    m_shortName = websiteUrl.section('/', -1);
    m_websiteUrl = QUrl(websiteUrl);
}

void WowAddon::setIsInstalled(bool isInstalled)
{
    if (m_isInstalled == isInstalled) {
        return;
    }
    m_isInstalled = isInstalled;
    emit isInstalledChanged(isInstalled);
}

void WowAddon::setVersionInstalled(const QString &versionInstalled)
{
    if (m_versionInstalled == versionInstalled) {
        return;
    }
    m_versionInstalled = versionInstalled;
    emit versionInstalledChanged(versionInstalled);
}

void WowAddon::addFile(const WowAddon::File& file)
{
    m_files << file;
}

void WowAddon::setSummary(const QString &summary)
{
    m_summary = summary;
}
