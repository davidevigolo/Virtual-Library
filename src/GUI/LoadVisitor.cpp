#include <LoadVisitor.h>

LoadVisitor::LoadVisitor(QMap<QString, QVector<MediaItem *>> &mediaItems) : mediaItems(mediaItems) {}

void LoadVisitor::visit(MediaItem *media)
{
    qErrnoWarning("Cannot load a MediaItem");
}

void LoadVisitor::visit(Readable *readable)
{
    qErrnoWarning("Cannot load a Readable");
}

void LoadVisitor::visit(AudioVisual *audioVisual)
{
    qErrnoWarning("Cannot load an AudioVisual");
}

void LoadVisitor::visit(Article *item)
{
    mediaItems["Article"].push_back(item);
}

void LoadVisitor::visit(Book *item)
{
    mediaItems["Book"].push_back(item);
}

void LoadVisitor::visit(Film *item)
{
    mediaItems["Film"].push_back(item);
}

void LoadVisitor::visit(Music *item)
{
    mediaItems["Music"].push_back(item);
}

void LoadVisitor::visit(Podcast *item)
{
    mediaItems["Podcast"].push_back(item);
}