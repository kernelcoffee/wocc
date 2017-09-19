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
    case Categories: {
        QStringList result;
        for (auto cat : addon->categories()) {
            result.append(cat.name);
        }
        return result.join(", ");
    }
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
    if (row < 0 || row > m_data.count()) {
        return nullptr;
    }
    qDebug() << row;
    return m_data[row];
}

void CurseAddonModel::setData(const QVector<Curse::Addon*>& data)
{
    beginResetModel();
    m_data = data;
    endResetModel();
}
