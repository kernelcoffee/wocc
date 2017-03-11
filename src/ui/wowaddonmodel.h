#ifndef WOWADDONMODEL_H
#define WOWADDONMODEL_H

#include <QAbstractListModel>

class WowAddon;

class WowAddonModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        Name = Qt::UserRole,
        InstallCount,
        Categories,
        Authors,
        Installed,
        VersionInstalled,
        VersionAvailable
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
