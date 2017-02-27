#include "databasecore.h"
#include "coremanager.h"
#include "Network/filedownloader.h"

#include <QStandardPaths>
#include <QProcess>
#include <QXmlStreamReader>

#include <QDebug>


static constexpr char database_url[] = "http://clientupdate.curse.com/feed/Complete.xml.bz2";

DatabaseCore::DatabaseCore(CoreManager *parent) :
    AbstractCore(parent)
  , m_network(parent->network())
{
}

DatabaseCore::~DatabaseCore()
{
    qDeleteAll(m_database);
}

QVector<WowAddon*> DatabaseCore::addonList() const
{
    return addonList();
}

void DatabaseCore::update(bool isAsync)
{
    qDebug() << m_network;
    FileDownloader *downloader =  m_network->createFileDownloader();
    downloader->setUrl(database_url);
    downloader->setFileOverride(true);
    downloader->setDestination(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));

    connect(downloader, &FileDownloader::finished, [this, downloader](){
            inflate(downloader->savedFileLocation());
            downloader->deleteLater();
            emit wowAddonListUpdated(m_database);
    });

    if (isAsync) {
        downloader->start();
    } else {
        downloader->startSync();
    }
}

bool DatabaseCore::inflate(const QString filePath)
{
    QProcess process(this);
    process.start("bzip2", {"-dkc", filePath});
    if (!process.waitForStarted()) {
        return false;
    }

    if (!process.waitForFinished()) {
        return false;
    }

    qDebug() << "filePath decompressed";
    parseToDatabase(process.readAll());
    return true;
}

void DatabaseCore::parseToDatabase(const QString& data)
{
    QXmlStreamReader reader(data);

    int n = 0;
    while (!reader.atEnd()) {
        reader.readNextStartElement();
        if (reader.isStartElement() && reader.name() == "CAddOn") {
            if (++n > 1)
                continue;
            WowAddon* addon = new WowAddon;

            while (!reader.isEndElement() || reader.name() != "CAddOn") {
                reader.readNextStartElement();

                // Authors
                if (reader.name() == "Authors") {
                    reader.readNextStartElement();
                    while (reader.isStartElement() && reader.name() == "CAddOnAuthor") {
                        reader.readNextStartElement();
                        QString name = reader.readElementText();
                        reader.readNextStartElement();
                        QString url = reader.readElementText();
                        addon->addAuthor(name, url);
                        reader.readNextStartElement();
                        reader.readNextStartElement();
                    }
                }

                // Categories
                if (reader.name() == "Categories") {
                    reader.readNextStartElement();
                    while (reader.isStartElement() && reader.name() == "CAddOnCategory") {
                        reader.readNextStartElement();
                        int id = reader.readElementText().toInt();
                        reader.readNextStartElement();
                        QString name = reader.readElementText();
                        reader.readNextStartElement();
                        QString url = reader.readElementText();
                        addon->addCategory(id, name, url);
                        reader.readNextStartElement();
                        reader.readNextStartElement();
                    }
                }
                // CategorySection
                if (reader.name() == "CategorySection") {
                    reader.readNextStartElement();
                    // ExtraIncludePattern
                    reader.readNextStartElement();
                    // GameID
                    reader.readNextStartElement();
                    // ID
                    reader.readNextStartElement();
                    // InitialInclusionPattern
                    reader.readNextStartElement();
                    // Name
                    reader.readNextStartElement();
                    // PackageType
                    reader.readNextStartElement();
                    // PackageType
                    reader.readNextStartElement();
                }

                // CommentCount
                // DefaultFileId
                // DonationUrl
                // DownloadCount
                // ExternalUrl
                // GameId
                // IconId
                // Id
                if (reader.name() == "Id") {
                    addon->setId(reader.readElementText().toInt());
                    reader.readNextStartElement();
                }
                // Install Count
                if (reader.name() == "InstallCount") {
                    addon->setInstallCount(reader.readElementText().toInt());
                    reader.readNextStartElement();
                }
                // LatestFiles
                if (reader.name() == "LatestFiles") {
                    reader.readNextStartElement();
                    // CAddOnFile
                    reader.readNextStartElement();
                    // AlternateFileId
                    // Dependencies
                    while (reader.isStartElement() && reader.name() == "CAddOnCategory") {
                        // CAddOnFileDependency
                        // AddOnId
                        // Type
                        reader.readNextStartElement();
                    }
                    // DownloadURL
                    // FileDate
                    // FileName
                    // FileStatus
                    // GameVersion
                    // a:string
                    // Id
                    // IsAlternate
                    // IsAvailable
                    // Modules
                    while (reader.isStartElement() && reader.name() == "CAddOnCategory") {
                        // CAddOnModule
                        // Fingerprint
                        // Foldername
                        reader.readNextStartElement();
                    }
                    // PackageFingerprint
                    // ReleaseType
                }
                // Likes
                // Name
                if (reader.name() == "Name") {
                    addon->setName(reader.readElementText());
                    reader.readNextStartElement();
                }
                // PackageType
                // PrimaryAuthorName
                // PrimaryCategoryId
                // Rating
                // Stage
                // Status
                // Summary
                if (reader.name() == "Summary") {
                    addon->setSummary(reader.readElementText());
                    reader.readNextStartElement();
                }
                // WebSiteURL

            }
            m_database << addon;
        }
    }
    qDebug() << m_database.count() << "addons loaded.";
}
