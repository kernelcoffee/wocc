#include "wowaddonmodel.h"
#include <QDebug>
WowAddonModel::WowAddonModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

QVariant WowAddonModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(index)
    Q_UNUSED(role)
    return QVariant();
}

int WowAddonModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 0;
}

QHash<int, QByteArray> WowAddonModel::roleNames() const
{
    return {};
}

void WowAddonModel::setData(const QVector<WowAddon*>& data)
{
    m_data = data;
    emit dataChanged(index(0), index(data.count()));
    qDebug() << "data set";
}
