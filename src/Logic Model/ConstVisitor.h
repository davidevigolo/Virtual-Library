#ifndef CONST_VISITOR_H
#define CONST_VISITOR_H
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

class ConstVisitor {
    public:
        virtual ~ConstVisitor() = default;

        virtual void visit(const MediaItem* media) = 0;
        virtual void visit(const Readable* readable) = 0;
        virtual void visit(const AudioVisual* audioVisual) = 0;
        virtual void visit(const Article* articles) = 0;
        virtual void visit(const Book* book) = 0;
        virtual void visit(const Film* film) = 0;
        virtual void visit(const Podcast* podcast) = 0;
        virtual void visit(const Music* music) = 0;
};
#endif // !VISITOR_H
