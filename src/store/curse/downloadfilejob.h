#ifndef DOWNLOADFILEJOB_H
#define DOWNLOADFILEJOB_H

#include "abstracts/abstractjob.h"
namespace Curse {
class DownloadFileJob : public AbstractJob
{
    Q_OBJECT
public:
    explicit DownloadFileJob( QObject *parent = 0);

    void run();

signals:
    void fileDownloaded(const QString& path);
};
}

#endif // DOWNLOADFILEJOB_H
