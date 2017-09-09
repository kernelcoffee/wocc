#ifndef ABSTRACTGAME_H
#define ABSTRACTGAME_H

#include <QObject>

class AddOn;
class AbstractTask;

class AbstractGame : public QObject
{
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)

    Q_OBJECT
public:
    AbstractGame(QObject* parent = 0);

    virtual AbstractTask* refresh();
    virtual AbstractTask* detect();

    virtual QString location() const;

signals:
    void locationChanged(const QString&);

public slots:
    virtual void setLocation(const QString&);

protected:
    QString m_location;
};

#endif // ABSTRACTGAME_H
