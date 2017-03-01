#ifndef WOWADDON_H
#define WOWADDON_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QDateTime>
#include <QList>

class WowAddon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint id READ id CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString shortName READ shortName CONSTANT)
    Q_PROPERTY(QUrl websiteUrl READ websiteUrl CONSTANT)
    Q_PROPERTY(QString summary READ summary CONSTANT)
    Q_PROPERTY(uint installCount READ installCount CONSTANT)
    Q_PROPERTY(QList<Author> authors READ authors CONSTANT)

public:
    struct Category {
        int id;
        QString name;
        QString url;
    };

    struct Author {
        QString name;
        QString url;
    };

    struct Module {
        QString folderName;
        QString fingerprint;
    };

    struct File {
        QString downloadUrl;
        QString name;
        QDateTime date;
        QList<Module> modules;
    };

    explicit WowAddon(QObject *parent = nullptr);

    uint id() const;
    QString name() const;
    QString shortName() const;
    QString summary() const;
    uint installCount() const;

    void addAuthor(const QString& name, const QString& url);
    void addCategory(int id, const QString& name, const QString& url);
    void addFolder(const QString& name, const QString& fingerprint);

    QList<Author> authors() const;
    QList<File> files();
    QUrl websiteUrl() const;

    void printContent();

public slots:
    void setId(uint id);
    void setName(const QString &name);
    void setSummary(const QString &summary);
    void setInstallCount(uint installCount);
    void setWebsiteUrl(const QString &websiteUrl);
    void addFile(const File &file);

private:
    uint m_id;
    QString m_name;
    QString m_shortName;
    QString m_summary;
    uint m_installCount;
    QUrl m_websiteUrl;

    QList<Author> m_authors;
    QList<Category> m_categories;
    QList<File> m_files;
};

#endif // WOWADDON_H
