#ifndef INSTALLTASK_H
#define INSTALLTASK_H

#include "abstracts/abstracttask.h"

#include <QUrl>

class FileDownloader;

namespace Curse {

class Addon;

class InstallTask : public AbstractTask
{
    Q_OBJECT
public:
    explicit InstallTask(Addon* addon, FileDownloader* downloader, QObject* parent = nullptr);
    ~InstallTask();

    virtual void start() override;
    virtual void cancel() override;

private:
    void onDownloadFinished();

    QUrl m_dest;
    Addon* m_addon = nullptr;
    FileDownloader* m_downloader = nullptr;
};

}


#endif // INSTALLTASK_H
