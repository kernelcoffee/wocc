#ifndef WOWADDONDETECTIONWORKER_H
#define WOWADDONDETECTIONWORKER_H

#include <QThread>
#include <QVector>
#include <QMap>

class WowAddon;

class WowAddonDetectionWorker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint progress READ progress NOTIFY progressChanged)
public:
    explicit WowAddonDetectionWorker(const QVector<WowAddon*> &library, QObject *parent = nullptr);

    void run();

    uint progress() const;

    static QStringList getPossibleAddons(const QVector<WowAddon*> &library);
    static QVector<WowAddon*> getInstalledAddons(const QStringList &possibleAddons, const QVector<WowAddon*> &library);
    static QMap<QString, QString> getInfosFromToc(const QString &tocPath);
signals:
    void error(const QString& errString);
    void succcess(const QVector<WowAddon*> &installAddons);
    void progressChanged(uint progress);

private:

    QVector<WowAddon*> m_library;
    uint m_progress;
};

#endif // WOWADDONDETECTIONWORKER_H
