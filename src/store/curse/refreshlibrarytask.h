#ifndef REFRESHLIBRARYTASK_H
#define REFRESHLIBRARYTASK_H

#include "abstracts/abstracttask.h"

class FileDownloader;

namespace Curse {

class Addon;

class RefreshLibraryTask : public AbstractTask
{
    Q_OBJECT
public:
    explicit RefreshLibraryTask(FileDownloader* downloader, QObject* parent = nullptr);
    ~RefreshLibraryTask();

    virtual void start() override;
    virtual void cancel() override;

signals:
    void finished(const QVector<Curse::Addon*>& library);

private:
    void onDownloadFinished();

    FileDownloader* m_downloader;
};

}
#endif // REFRESHLIBRARYTASK_H
