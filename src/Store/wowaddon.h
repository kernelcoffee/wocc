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
    Q_PROPERTY(bool isInstalled READ isInstalled NOTIFY isInstalledChanged)
    Q_PROPERTY(QString versionInstalled READ versionInstalled NOTIFY versionInstalledChanged)
    Q_PROPERTY(QString versionAvailable READ versionAvailable CONSTANT)

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
        QString version;
        QList<Module> modules;
    };

    explicit WowAddon(QObject *parent = nullptr);


    void addAuthor(const QString& name, const QString& url);
    void addCategory(int id, const QString& name, const QString& url);

    void printContent();

    uint id() const;
    QString name() const;
    QString shortName() const;
    QString summary() const;
    uint installCount() const;
    QList<Author> authors() const;
    QList<File> files();
    QUrl websiteUrl() const;
    bool isInstalled() const;
    QString versionInstalled() const;
    QString versionAvailable() const;

public slots:
    void addFile(const File &file);

    void setId(uint id);
    void setName(const QString &name);
    void setSummary(const QString &summary);
    void setInstallCount(uint installCount);
    void setWebsiteUrl(const QString &websiteUrl);
    void setIsInstalled(bool installed);
    void setVersionInstalled(const QString &versionInstalled);

signals:
    void isInstalledChanged(bool isInstalled);
    void versionInstalledChanged(const QString &versionInstalled);

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
    bool m_isInstalled = false;
    QString m_versionInstalled;
    QString m_versionAvailable;
};

#endif // WOWADDON_H
