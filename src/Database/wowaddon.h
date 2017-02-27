#ifndef WOWADDON_H
#define WOWADDON_H

#include <QObject>
#include <QString>
#include <QXmlStreamAttributes>

class WowAddon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString summary READ summary WRITE setSummary NOTIFY summaryChanged)
    Q_PROPERTY(uint installCount READ installCount WRITE setInstallCount NOTIFY installCountChanged)

    struct Category {
        int id;
        QString name;
        QString url;
    };

public:
    explicit WowAddon(QObject *parent = nullptr);

    QString name() const;
    QString summary() const;
    uint installCount() const;

    void addAuthor(const QString& name, const QString& url);
    void addCategory(int id, const QString& name, const QString& url);

signals:
    void nameChanged(QString name);
    void summaryChanged(QString summary);
    void installCountChanged(uint installCount);

public slots:
    void setName(QString name);
    void setSummary(QString summary);
    void setInstallCount(uint installCount);

private:
    QString m_name;
    QString m_summary;
    uint m_installCount;

    QList<QPair<QString, QString>> m_authors;
    QList<Category> m_categories;
};

#endif // WOWADDON_H
