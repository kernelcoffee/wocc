#include "wowaddonmodel.h"
#include "Database/wowaddon.h"
#include <QDebug>

WowAddonModel::WowAddonModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

QVariant WowAddonModel::data(const QModelIndex& index, int role) const
{
    if (m_data.isEmpty() || index.row() < 0 || index.row() > rowCount())
        return QVariant();

    WowAddon* addon = m_data.at(index.row());

    switch (role) {
    case Name:
        return addon->name();
    case Authors:
        if (addon->authors().count() > 0)
            return addon->authors().first().name;
        break;
    }
    return "Invalid";
}

int WowAddonModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

QHash<int, QByteArray> WowAddonModel::roleNames() const
{
    return {
        {Name, "name"},
        {Categories, "categories"},
        {InstallCount, "installCount"},
        {Authors, "authors"}
    };
}

void WowAddonModel::setData(const QVector<WowAddon*>& data)
{
    qDebug() << "Update data" << data.count();
    beginResetModel();
    m_data = data;
    endResetModel();
}
