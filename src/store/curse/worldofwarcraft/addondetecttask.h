#ifndef ADDONDETECTJOB_H
#define ADDONDETECTJOB_H


#include "abstracts/abstracttask.h"

#include <QVector>
#include <QMap>

namespace Curse {
class Addon;
}

class AddonDetectTask : public AbstractTask
{
    Q_OBJECT
public:
    explicit AddonDetectTask(const QVector<Curse::Addon*>& library, QObject* parent = nullptr);

    void run();

    static QStringList getPossibleAddons(const QString& path, const QVector<Curse::Addon*>& library);
    static QVector<Curse::Addon*> getInstalledAddons(const QStringList& possibleAddons,
                                                     const QVector<Curse::Addon*>& library);
    static QMap<QString, QString> getInfosFromToc(const QString& tocPath);
signals:
    void error(const QString& errString);
    void succcess(const QVector<Curse::Addon*>& installAddons);

private:
    QVector<Curse::Addon*> m_library;
};

#endif // ADDONDETECTJOB_H
