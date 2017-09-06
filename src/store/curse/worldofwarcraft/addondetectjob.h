#ifndef ADDONDETECTJOB_H
#define ADDONDETECTJOB_H

#include <QThread>
#include <QVector>
#include <QMap>

namespace Curse {
class Addon;
}

class AddonDetectJob : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint progress READ progress NOTIFY progressChanged)
public:
    explicit AddonDetectJob(const QVector<Curse::Addon*> &library, QObject *parent = nullptr);

    void run();

    uint progress() const;

    static QStringList getPossibleAddons(const QString &path, const QVector<Curse::Addon*> &library);
    static QVector<Curse::Addon*> getInstalledAddons(const QStringList &possibleAddons, const QVector<Curse::Addon*> &library);
    static QMap<QString, QString> getInfosFromToc(const QString &tocPath);
signals:
    void error(const QString& errString);
    void succcess(const QVector<Curse::Addon*> &installAddons);
    void progressChanged(uint progress);

private:

    QVector<Curse::Addon*> m_library;
    uint m_progress;
};

#endif // ADDONDETECTJOB_H