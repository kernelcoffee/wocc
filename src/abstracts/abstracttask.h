#ifndef ABSTRACTJOB_H
#define ABSTRACTJOB_H

#include <QObject>

class AbstractTask : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(uint progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(Status status READ status WRITE setStatus NOTIFY statusChanged)

public:
    enum Status {
        Idle,
        Running,
        Success,
        Failed
    };

    explicit AbstractTask(QObject* parent = 0);

    QString name() const;
    uint progress() const;
    Status status() const;

public slots:
    void setProgress(uint progress);
    void setStatus(Status status);

signals:
    void progressChanged(uint progress);
    void statusChanged(Status status);

protected:
    QString m_name;
    uint m_progress = 0;
    Status m_status = Idle;
};

Q_DECLARE_METATYPE(AbstractTask::Status)


#endif // ABSTRACTJOB_H
