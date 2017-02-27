#ifndef WOWADDONMODEL_H
#define WOWADDONMODEL_H

#include <QAbstractListModel>
#include "Database/wowaddon.h"

class WowAddonModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        Name = Qt::UserRole,
    };

    WowAddonModel(QObject *parent = 0);

    QVariant                data(const QModelIndex &index, int role) const override;
    int                     rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray>  roleNames() const override;

public slots:
    void setData(const QVector<WowAddon*>& data);

private:
    QVector<WowAddon*> m_data;
};

#endif // WOWADDONMODEL_H
