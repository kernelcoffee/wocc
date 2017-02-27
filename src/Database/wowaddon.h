#ifndef WOWADDON_H
#define WOWADDON_H

#include <QObject>
#include <QString>
#include <QXmlStreamAttributes>

class WowAddon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint id READ id CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString summary READ summary CONSTANT)
    Q_PROPERTY(uint installCount READ installCount CONSTANT)
    Q_PROPERTY(QList<Author> authors READ authors CONSTANT)


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

    uint id() const;
    QString name() const;
    QString summary() const;
    uint installCount() const;

    void addAuthor(const QString& name, const QString& url);
    void addCategory(int id, const QString& name, const QString& url);

    QList<Author> authors() const;

public slots:
    void setId(uint id);
    void setName(const QString &name);
    void setSummary(const QString &summary);
    void setInstallCount(uint installCount);

private:
    uint m_id;
    QString m_name;
    QString m_summary;
    uint m_installCount;

    QList<Author> m_authors;
    QList<Category> m_categories;
};

#endif // WOWADDON_H
