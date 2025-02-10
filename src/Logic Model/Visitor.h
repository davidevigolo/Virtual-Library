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

class Visitor : QObject {
public:
    virtual ~Visitor() = default;

    virtual QJsonObject visit(MediaItem* media) = 0;
    virtual QJsonObject visit(Readable* readable) = 0;
    virtual QJsonObject visit(AudioVisual* audioVisual) = 0;
    virtual QJsonObject visit(Article* articles) = 0;
    virtual QJsonObject visit(Book* book) = 0;
    virtual QJsonObject visit(Film* film) = 0;
    virtual QJsonObject visit(Podcast* podcast) = 0;
    virtual QJsonObject visit(Music* music) = 0;
};
#endif // !VISITOR_H
