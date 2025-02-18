#ifndef XML_VISITOR
#define XML_VISITOR

#include <QJsonObject>
#include <QJsonArray>
#include <utility>
#include <QXmlStreamWriter>
#include <MediaItem.h>
#include <Readable.h>
#include <AudioVisual.h>
#include <Article.h>
#include <Book.h>
#include <Film.h>
#include <Podcast.h>
#include <Music.h>

class XmlVisitor : public ConstVisitor{
private:
    QXmlStreamWriter& writer;
public:
    XmlVisitor(QXmlStreamWriter& _writer) : writer(_writer) {};
    virtual ~XmlVisitor() = default;

    void visit(const MediaItem* media);
    void visit(const Readable* readable);
    void visit(const AudioVisual* audioVisual);
    void visit(const Article* articles);
    void visit(const Book* book);
    void visit(const Film* film);
    void visit(const Podcast* podcast);
    void visit(const Music* music);
};

#endif // !XML_VISITOR