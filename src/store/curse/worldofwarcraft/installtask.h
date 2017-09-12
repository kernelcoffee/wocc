#ifndef INSTALLTASK_H
#define INSTALLTASK_H

#include "abstracts/abstracttask.h"

class FileDownloader;

namespace Curse {

class Addon;

class InstallTask : public AbstractTask
{
    Q_OBJECT
public:
    explicit InstallTask(Addon* addon, FileDownloader* downloader, QObject* parent = nullptr);

    virtual void start() override;
    virtual void cancel() override;

private:
    Addon* m_addon;
    FileDownloader* m_downloader;
};

}


#endif // INSTALLTASK_H
