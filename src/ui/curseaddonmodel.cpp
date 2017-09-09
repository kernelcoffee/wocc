#include "curseaddonmodel.h"
#include "store/curse/addon.h"
#include <QDebug>

CurseAddonModel::CurseAddonModel(QObject* parent) :
    QAbstractListModel(parent)
{

}

QVariant CurseAddonModel::data(const QModelIndex& index, int role) const
{
    if (m_data.isEmpty() || index.row() < 0 || index.row() > rowCount())
        return QVariant();

    Curse::Addon* addon = m_data.at(index.row());

    switch (role) {
    case Name:
        return addon->name();
    case Authors:
        if (addon->authors().count() > 0)
            return addon->authors().first().name;
        break;
    case Installed:
        return addon->isInstalled();
    case InstallCount:
        return addon->installCount();
    case VersionAvailable:
        return addon->versionAvailable();
    case VersionInstalled:
        return addon->versionInstalled();
    }
    return "Invalid";
}

int CurseAddonModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

QHash<int, QByteArray> CurseAddonModel::roleNames() const
{
    return {
        {Name, "name"},
        {Categories, "categories"},
        {InstallCount, "installCount"},
        {Authors, "authors"},
        {Installed, "isInstalled"},
        {VersionAvailable, "versionAvailable"},
        {VersionInstalled, "versionInstalled"}
    };
}

Curse::Addon* CurseAddonModel::getAddon(int row)
{
    return m_data[row];
}

void CurseAddonModel::setData(const QVector<Curse::Addon*>& data)
{
    qDebug() << "Update data" << data.count();
    beginResetModel();
    m_data = data;
    endResetModel();
}
