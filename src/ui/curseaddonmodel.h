#ifndef CURSEADDONMODEL_H
#define CURSEADDONMODEL_H

#include <QAbstractListModel>

namespace Curse {
    class Addon;
}

class CurseAddonModel : public QAbstractListModel
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

    CurseAddonModel(QObject *parent = 0);

    QVariant                data(const QModelIndex &index, int role) const override;
    int                     rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray>  roleNames() const override;

public slots:
    void setData(const QVector<Curse::Addon*>& data);

private:
    QVector<Curse::Addon*> m_data;
};

#endif // CURSEADDONMODEL_H
