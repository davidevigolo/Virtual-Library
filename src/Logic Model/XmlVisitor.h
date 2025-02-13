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

    void visit(const MediaItem* media);
    void visit(const Readable* readable);
    void visit(const AudioVisual* audioVisual);
    void visit(const Article* articles);
    void visit(const Book* book);adable);
    void visit(const AudioVisual* audioVisual);
    void visit(const Article* articles);
    void visit(const Book* book);
    void visit(const Film* film);
    void visit(const Podcast* podcast);
    void visit(const Music* music);
};

#endif // !XML_VISITOR