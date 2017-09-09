#ifndef ABSTRACTGAME_H
#define ABSTRACTGAME_H

#include <QObject>

class AddOn;
class AbstractWorker;

class AbstractGame : public QObject
{
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)

    Q_OBJECT
public:
    AbstractGame(QObject *parent = 0);

    virtual AbstractWorker* refresh();
    virtual AbstractWorker* detect();

    virtual QString location() const;

signals:
    void locationChanged(const QString& location);

public slots:
    virtual void setLocation(const QString& location);

protected:
    QString m_location;
};

#endif // ABSTRACTGAME_H
