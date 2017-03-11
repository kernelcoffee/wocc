#include "fileextractor.h"

#include <QProcess>
#include <QDebug>

FileExtractor::FileExtractor(QObject *parent) :
    QObject(parent)
{

}

QString FileExtractor::bzip2FileToString(const QString &filePath)
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
    QProcess process;
    process.start("unzip", {filePath, "-du", destination});
    if (!process.waitForStarted()) {
        return false;
    }
    if (!process.waitForFinished()) {
        return false;
    }

    qDebug() << filePath << "unzip to" << destination;
    return true;
}
