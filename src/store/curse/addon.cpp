#include "addon.h"
#include <QDebug>

using namespace Curse;

Addon::Addon(QObject* parent) :
    AbstractAddon(parent)
{
}

void Addon::addAuthor(const QString& name, const QString& url)
{
    m_authors.append(Author({name, url}));
}

void Addon::addCategory(int id, const QString& name, const QString& url)
{
    m_categories.append(Category({id, name, url}));
}

void Addon::printContent()
{
    qDebug() << m_name << m_shortName;
    for (auto file : m_files) {
        qDebug() << "Url :" << file.name << file.downloadUrl;
        for (auto module : file.modules) {
            qDebug() << "dependency : " << module.folderName;
        }
        qDebug();
    }
}

uint Addon::id() const
{
    return m_id;
}

uint Addon::gameId() const
{
    return m_gameId;
}

QString Addon::shortName() const
{
    return m_shortName;
}

bool Addon::isInstalled() const
{
    return m_isInstalled;
}

QString Addon::versionInstalled() const
{
    return m_versionInstalled;
}

QString Addon::versionAvailable() const
{
    return m_files.first().version;
}

QUrl Addon::folderPath() const
{
    return m_folderPath;
}

bool Addon::updateAvailable() const
{
    return m_updateAvailable;
}

QString Addon::summary() const
{
    return m_summary;
}

uint Addon::installCount() const
{
    return m_installCount;
}

QList<Addon::Author> Addon::authors() const
{
    return m_authors;
}

QList<Addon::File> Addon::files()
{
    return m_files;
}

QUrl Addon::websiteUrl() const
{
    return m_websiteUrl;
}

void Addon::setId(uint id)
{
    m_id = id;
}

void Addon::setGameId(uint gameId)
{
    m_gameId = gameId;
}

void Addon::setInstallCount(uint installCount)
{
    m_installCount = installCount;
}

void Addon::setWebsiteUrl(const QString& websiteUrl)
{
    m_shortName = websiteUrl.section('/', -1);
    m_websiteUrl = QUrl(websiteUrl);
}

void Addon::setIsInstalled(bool isInstalled)
{
    if (m_isInstalled == isInstalled) {
        return;
    }
    m_isInstalled = isInstalled;
    emit isInstalledChanged(isInstalled);
}

void Addon::setVersionInstalled(const QString& versionInstalled)
{
    if (m_versionInstalled == versionInstalled) {
        return;
    }
    m_versionInstalled = versionInstalled;
    emit versionInstalledChanged(versionInstalled);
}

void Addon::addFile(const Addon::File& file)
{
    m_files << file;
}

void Addon::setSummary(const QString& summary)
{
    m_summary = summary;
}
