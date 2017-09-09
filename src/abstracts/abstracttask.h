#ifndef ABSTRACTJOB_H
#define ABSTRACTJOB_H

#include <QObject>
#include <QMutex>

class AbstractTask : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(uint progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(Status status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(bool isAutoDelete READ isAutoDelete WRITE setAutoDelete NOTIFY autoDeleteChanged)
    Q_PROPERTY(bool isUnique READ isUnique WRITE setIsUnique NOTIFY isUniqueChanged)


public:
    enum Status {
        Idle,
        Running,
        Success,
        Failed,
        Canceled
    };

    explicit AbstractTask(QObject* parent = 0);

    QString name() const;
    uint progress() const;
    Status status() const;

    bool isAutoDelete();
    bool isUnique() const;

    Q_INVOKABLE virtual void start();
    Q_INVOKABLE virtual void pause();
    Q_INVOKABLE virtual void cancel();

signals:
    void progressChanged(uint progress);
    void statusChanged(Status status);
    void autoDeleteChanged(bool isAutoDelete);
    void isUniqueChanged(bool isUnique);

    void finished();
    void cancelled();
    void failed();

public slots:
    void setProgress(uint progress);
    void setStatus(Status status);
    void setAutoDelete(bool autoDelete);

    void setIsUnique(bool isUnique);

protected:
    QString m_name;
    uint m_progress = 0;
    Status m_status = Idle;
    bool m_autoDelete = false;
    bool m_isUnique = false;

    mutable QMutex m_mutex;
};

Q_DECLARE_METATYPE(AbstractTask::Status)


#endif // ABSTRACTJOB_H
