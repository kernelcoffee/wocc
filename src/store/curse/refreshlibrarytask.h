#ifndef REFRESHLIBRARYTASK_H
#define REFRESHLIBRARYTASK_H

#include "abstracts/abstracttask.h"

class FileDownloader;

class RefreshLibraryTask : public AbstractTask
{
    Q_OBJECT
public:
    explicit RefreshLibraryTask(FileDownloader* downloader, QObject* parent = nullptr);
    ~RefreshLibraryTask();

    virtual void start() override;

private:
    void onFinished();

    FileDownloader* m_downloader;
};

#endif // REFRESHLIBRARYTASK_H
