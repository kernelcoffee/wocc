#ifndef ABSTRACTADDON_H
#define ABSTRACTADDON_H

#include <QObject>

class AbstractAddon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)

public:
    explicit AbstractAddon(QObject* parent = 0);

    QString name() const;
    QString author() const;

signals:
    void nameChanged(QString name);
    void authorChanged(QString author);

public slots:
    void setName(const QString& name);
    void setAuthor(const QString& author);

protected:
    QString m_name;
    QString m_author;
};

#endif // ABSTRACTADDON_H
