#include "fileextractor.h"

#include <QProcess>
#include <QDebug>
#include <quazip5/JlCompress.h>

FileExtractor::FileExtractor(QObject* parent) :
    QObject(parent)
{

}

QString FileExtractor::bzip2FileToString(const QString& filePath)
{
    QProcess process;
    process.start("bzip2", {"-dkc", filePath});
    if (!process.waitForStarted()) {
        return "";
    }

    if (!process.waitForFinished()) {
        return "";
    }

    qDebug() << filePath << "decompressed";
    return process.readAll();
}

bool FileExtractor::unzip(const QString& filePath, const QString& destination)
{
    JlCompress::extractDir(filePath, destination);

    qDebug() << filePath << "unzip to" << destination;
    return true;
}
