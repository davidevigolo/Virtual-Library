#ifndef LOADVISITOR_H
#define LOADVISITOR_H

#include <Visitor.h>
#include <QMap>
#include <QVector>
#include <MediaItem.h>
#include <Readable.h>
#include <AudioVisual.h>
#include <Article.h>
#include <Book.h>
#include <Film.h>
#include <Podcast.h>
#include <Music.h>

class LoadVisitor : public Visitor {
    private:
        QMap<QString, QVector<MediaItem*>>& mediaItems;
    public:
        LoadVisitor(QMap<QString, QVector<MediaItem*>>& mediaItems);
        virtual void visit(MediaItem* media);
        virtual void visit(Readable* readable);
        virtual void visit(AudioVisual* audioVisual);
        virtual void visit(Article* articles);
        virtual void visit(Book* book);
        virtual void visit(Film* film);
        virtual void visit(Podcast* podcast);
        virtual void visit(Music* music);
};
#endif // !LOADVISITOR_H