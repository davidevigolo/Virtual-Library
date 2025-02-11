#ifndef XML_VISITOR
#define XML_VISITOR

#include <QJsonObject>
#include <QJsonArray>
#include <utility>
#include <QXmlStreamWriter>

class MediaItem;
class Readable;
class AudioVisual;
class Article;
class Book;
class Film;
class Podcast;
class Music;

class XmlVisitor {
private:
    QXmlStreamWriter& writer;
public:
    XmlVisitor(QXmlStreamWriter& _writer) : writer(_writer) {};
    virtual ~XmlVisitor() = default;

    void visit(MediaItem* media, bool onlyBody = false);
    void visit(Readable* readable, bool onlyBody = false);
    void visit(AudioVisual* audioVisual, bool onlyBody = false);
    void visit(Article* articles, bool onlyBody = false);
    void visit(Book* book, bool onlyBody = false);
    void visit(Film* film, bool onlyBody = false);
    void visit(Podcast* podcast, bool onlyBody = false);
    void visit(Music* music, bool onlyBody = false);
};

#endif // !XML_VISITOR