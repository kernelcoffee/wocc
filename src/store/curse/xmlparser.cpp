#include "xmlparser.h"
#include "addon.h"

#include <QXmlStreamReader>
#include <QDebug>

using namespace Curse;

inline void parseAuthors(QXmlStreamReader& reader, Addon* addon)
{
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

inline void parseCategories(QXmlStreamReader& reader, Addon* addon)
{
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

inline void parseCategorySection(QXmlStreamReader& reader, Addon* addon)
{
    Q_UNUSED(addon)
    // ExtraIncludePattern
    reader.readNextStartElement();
    // qDebug() << "ExtraIncludePattern" << reader.name() << reader.tokenString();
    reader.readNextStartElement();
    // GameID
    reader.readNextStartElement();
    // qDebug() << "GameID" << reader.name() << reader.tokenString();
    reader.readNextStartElement();
    // ID
    reader.readNextStartElement();
    // qDebug() << "ID" << reader.name() << reader.tokenString();
    reader.readNextStartElement();
    // InitialInclusionPattern
    reader.readNextStartElement();
    // qDebug() << "InitialInclusionPattern" << reader.name() << reader.tokenString();
    reader.readNextStartElement();
    // Name
    reader.readNextStartElement();
    // qDebug() << "Name" << reader.name() << reader.tokenString();
    reader.readNextStartElement();
    // PackageType
    reader.readNextStartElement();
    // qDebug() << "PackageType" << reader.name() << reader.tokenString();
    reader.readNextStartElement();
    // Path
    reader.readNextStartElement();
    // qDebug() << "Path" << reader.name() << reader.tokenString();
    reader.readNextStartElement();
    //-----
    reader.readNextStartElement();
}

inline void parseLatestFiles(QXmlStreamReader& reader, Addon* addon)
{
    Addon::File file;

    reader.readNextStartElement();
    // qDebug() << "CAddonFile" << reader.name() << reader.tokenString();
    while (reader.isStartElement() && reader.name() == "CAddOnFile") {
        //qDebug() << "======= NEW CAFILE =======";
        // AlternateFileId
        reader.readNextStartElement();
        // qDebug() << "AlternateFileId" << reader.name() << reader.tokenString();
        reader.readNextStartElement();

        // Dependencies
        reader.readNextStartElement();
        // qDebug() << "Dependencies" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        // CAddOnFileDependency
        // qDebug() << "CAddOnFileDependency" << reader.name() << reader.tokenString();
        while (reader.isStartElement() && reader.name() == "CAddOnFileDependency") {
            // AddOnId
            reader.readNextStartElement();
            int id = reader.readElementText().toInt();
            //qDebug() << "AddOnId" << reader.name() << reader.tokenString() << id;
            // Type
            reader.readNextStartElement();
            QString category = reader.readElementText();
            //qDebug() << "Type" << reader.name() << reader.tokenString() << category;
            reader.readNextStartElement();
            reader.readNextStartElement();
            addon->addDependency(id, category);
        }

        // DownloadURL
        reader.readNextStartElement();
        // qDebug() << "DownloadURL" << reader.name() << reader.tokenString();
        file.downloadUrl = reader.readElementText();

        // FileDate
        reader.readNextStartElement();
        if (reader.name() != "FileDate") {
            qDebug() << "FileDate" << reader.name() << reader.tokenString();
        }
        file.date = QDateTime::fromString(reader.readElementText(), Qt::ISODate);
        // FileName
        reader.readNextStartElement();
        file.version = reader.readElementText();
        // FileStatus
        reader.readNextStartElement();
        if (reader.name() != "FileStatus") {
            qDebug() << "FileStatus" << reader.name() << reader.tokenString();
        }
        reader.readNextStartElement();
        // GameVersion
        reader.readNextStartElement();
        if (reader.name() != "GameVersion" || !reader.isStartElement()) {
            qDebug() << "GameVersion" << reader.name() << reader.tokenString();
        }
        reader.readNextStartElement();
        while (reader.name() == "string") {
            reader.readNextStartElement();
            // Game version values
        }
        // Id
        reader.readNextStartElement();
        if (reader.name() != "Id" || !reader.isStartElement()) {
            qDebug() << "Id" << reader.name() << reader.tokenString();
        }
        reader.readNextStartElement();
        // IsAlternate
        reader.readNextStartElement();
        if (reader.name() != "IsAlternate" || !reader.isStartElement()) {
            qDebug() << "IsAlternate" << reader.name() << reader.tokenString();
        }
        reader.readNextStartElement();
        // IsAvailable
        reader.readNextStartElement();
        if (reader.name() != "IsAvailable" || !reader.isStartElement()) {
            qDebug() << "IsAvailable" << reader.name() << reader.tokenString();
        }
        reader.readNextStartElement();
        // Modules
        reader.readNextStartElement();
        if (reader.name() != "Modules" && reader.isStartElement()) {
            qDebug() << "Modules" << reader.name() << reader.tokenString();
        }
        // qDebug() << "Modules" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        // CAddOnModule
        // qDebug() << "CAddOnModule" << reader.name() << reader.tokenString();
        while (reader.isStartElement() && reader.name() == "CAddOnModule") {
            Addon::Module module;
            // Fingerprint
            reader.readNextStartElement();
            // qDebug() << "Fingerprint" << reader.name() << reader.tokenString();
            module.fingerprint = reader.readElementText();

            // Foldername
            reader.readNextStartElement();
            // qDebug() << "Foldername" << reader.name() << reader.tokenString();
            module.folderName = reader.readElementText();

            // CAddOnModule
            reader.readNextStartElement();
            // qDebug() << "/CAddOnModule"  << reader.name() << reader.tokenString();
            reader.readNextStartElement();
            // qDebug() << "CAddOnModule"  << reader.name() << reader.tokenString();
            file.modules << module;
        }
        // PackageFingerprint
        reader.readNextStartElement();
        if (reader.name() != "PackageFingerprint") {
            qDebug() << "PackageFingerprint" << reader.name() << reader.tokenString();
        }

        // qDebug() << "PackageFingerprint" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        // ReleaseType
        reader.readNextStartElement();
        // qDebug() << "ReleaseType" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        //qDebug() << "------------------------------------";
        reader.readNextStartElement();
        reader.readNextStartElement();
    }
    addon->addFile(file);
}

XmlParser::XmlParser(QObject* parent) :
    QObject(parent)
{

}

QVector<Addon*> XmlParser::XmlToAddonList(const QString& xml) const
{
    QXmlStreamReader reader(xml);
    QVector<Addon*> addonList;

    reader.readNextStartElement();
    reader.readNextStartElement();
    while (!reader.atEnd() && reader.isStartElement() && reader.name() == "CAddOn") {
        reader.readNextStartElement();

        Addon* addon = new Addon;

        // Authors
        if (reader.name() != "Authors") {
            qDebug() << "Authors" << reader.name() << reader.tokenString();
            qCritical() << "Parsing scheme changed";
            return addonList;
        }

        parseAuthors(reader, addon);
        reader.readNextStartElement();

        // Categories
        parseCategories(reader, addon);
        reader.readNextStartElement();

        // CategorySection
        parseCategorySection(reader, addon);
        reader.readNextStartElement();

        // CommentCount
        // qDebug() << "CommentCount" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        reader.readNextStartElement();

        // DefaultFileId
        // qDebug() << "DefaultFileId" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        reader.readNextStartElement();

        // DonationUrl
        // qDebug() << "DonationUrl" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        reader.readNextStartElement();

        // DownloadCount
        // qDebug() << "DownloadCount" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        reader.readNextStartElement();

        if (reader.name() != "ExternalUrl" && reader.isStartElement()) {
            qDebug() << "ExternalUrl"  << reader.name() << reader.tokenString();
            qCritical() << "Parsing scheme changed";
            return addonList;
        }

        // ExternalUrl
        // qDebug() << "ExternalUrl" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        reader.readNextStartElement();

        // GameId
        // qDebug() << "GameId" << reader.name() << reader.tokenString();
        addon->setGameId(reader.readElementText().toInt());
        reader.readNextStartElement();

        // IconId
        // qDebug() << "IconId" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        reader.readNextStartElement();

        // Id
        addon->setId(reader.readElementText().toUInt());
        reader.readNextStartElement();

        // Install Count
        addon->setInstallCount(reader.readElementText().toUInt());
        reader.readNextStartElement();

        // LatestFiles
        parseLatestFiles(reader, addon);
        reader.readNextStartElement();

        if (reader.name() != "Likes" && reader.isStartElement()) {
            qDebug() << "Likes"  << reader.name() << reader.tokenString();
            qCritical() << "Parsing scheme changed";
            return addonList;
        }

        // Likes
        //qDebug() << "Likes" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        reader.readNextStartElement();

        // Name
        //qDebug() << "Name" << reader.name() << reader.tokenString();
        addon->setName(reader.readElementText());
        reader.readNextStartElement();

        // PackageType
        // qDebug() << "PackageType" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        reader.readNextStartElement();

        // PrimaryAuthorName
        // qDebug() << "PrimaryAuthorName" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        reader.readNextStartElement();

        // PrimaryCategoryId
        // qDebug() << "PrimaryCategoryId" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        reader.readNextStartElement();

        // Rating
        // qDebug() << "Rating" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        reader.readNextStartElement();

        // Stage
        // qDebug() << "Stage" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        reader.readNextStartElement();

        // Status
        // qDebug() << "Status" << reader.name() << reader.tokenString();
        reader.readNextStartElement();
        reader.readNextStartElement();

        // Summary
        if (reader.name() != "Summary" && reader.isStartElement()) {
            qDebug() << "Summary"  << reader.name() << reader.tokenString();
            qCritical() << "Parsing scheme changed";
            return addonList;
        }
        addon->setSummary(reader.readElementText());
        reader.readNextStartElement();

        // WebSiteURL
        // qDebug() << "WebSiteURL" << reader.name() << reader.tokenString();
        addon->setWebsiteUrl(reader.readElementText());


        reader.readNextStartElement();
        reader.readNextStartElement();
        //qDebug() << "CAddon"  << reader.name() << reader.tokenString();


        addonList << addon;
    }

    qDebug() << addonList.count() << "addons loaded.";
    return addonList;
}
