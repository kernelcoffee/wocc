#ifndef DOWNLOADFILEJOB_H
#define DOWNLOADFILEJOB_H

#include "abstracts/abstracttask.h"
namespace Curse {
class DownloadFileJob : public AbstractTask
{
    Q_OBJECT
public:
    explicit DownloadFileJob( QObject* parent = 0);

    void run();

signals:
    void fileDownloaded(const QString& path);
};
}

#endif // DOWNLOADFILEJOB_H
