#ifndef VISITOR_H
#define VISITOR_H
#include <QJsonObject>
#include <QJsonArray>
#include <utility>


class MediaItem;
class Readable;
class AudioVisual;
class Article;
class Book;
class Film;
class Podcast;
class Music;


class Visitor {
    public:
        virtual ~Visitor() = default;

        virtual void visit(MediaItem* media) = 0;
        virtual void visit(Readable* readable) = 0;
        virtual void visit(AudioVisual* audioVisual) = 0;
        virtual void visit(Article* articles) = 0;
        virtual void visit(Book* book) = 0;
        virtual void visit(Film* film) = 0;
        virtual void visit(Podcast* podcast) = 0;
        virtual void visit(Music* music) = 0;
};
#endif // !VISITOR_H
