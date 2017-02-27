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
    Q_PROPERTY(QList<Author> authors READ authors NOTIFY authorsChanged)

    struct Category {
        int id;
        QString name;
        QString url;
    };

    struct Author {
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

    QList<Author> authors() const;

signals:
    void nameChanged(QString name);
    void summaryChanged(QString summary);
    void installCountChanged(uint installCount);
    void authorsChanged(QList<Author> authors);

public slots:
    void setName(QString name);
    void setSummary(QString summary);
    void setInstallCount(uint installCount);

private:
    QString m_name;
    QString m_summary;
    uint m_installCount;

    QList<Author> m_authors;
    QList<Category> m_categories;
};

#endif // WOWADDON_H
