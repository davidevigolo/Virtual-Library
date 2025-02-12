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

    void visit(const MediaItem* media, bool onlyBody = false);
    void visit(const Readable* readable, bool onlyBody = false);
    void visit(const AudioVisual* audioVisual, bool onlyBody = false);
    void visit(const Article* articles, bool onlyBody = false);
    void visit(const Book* book, bool onlyBody = false);
    void visit(const Film* film, bool onlyBody = false);
    void visit(const Podcast* podcast, bool onlyBody = false);
    void visit(const Music* music, bool onlyBody = false);
};

#endif // !XML_VISITOR