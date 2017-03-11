#ifndef FILEEXTRACTOR_H
#define FILEEXTRACTOR_H

#include <QObject>

class FileExtractor : public QObject
{
    Q_OBJECT
public:
    explicit FileExtractor(QObject *parent = 0);
    static QString bzip2FileToString(const QString &filePath);
    static bool unzip(const QString &filePath, const QString &destination);
};

#endif // FILEEXTRACTOR_H
