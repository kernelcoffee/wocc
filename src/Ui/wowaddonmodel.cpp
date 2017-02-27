#include "wowaddonmodel.h"
#include <QDebug>

WowAddonModel::WowAddonModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

QVariant WowAddonModel::data(const QModelIndex& index, int role) const
{
    qDebug() << role;
    if (m_data.isEmpty() || index.row() < 0 || index.row() > rowCount())
        return QVariant();

    WowAddon* addon = m_data.at(index.row());

    switch (role) {
    case Name:
        return addon->name();
    default:
        return "Invalid";
    }
    return QVariant();
}

int WowAddonModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    qDebug() << m_data.count();
    return m_data.count();
}

QHash<int, QByteArray> WowAddonModel::roleNames() const
{
    return {{Name, "name"}};
}

void WowAddonModel::setData(const QVector<WowAddon*>& data)
{
    beginResetModel();
    m_data = data;
    endResetModel();
    qDebug() << "new model" << m_data.count();
}
