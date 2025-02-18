#ifndef JSONVISITOR_H
#define JSONVISITOR_H

#include <ConstVisitor.h>
#include <ConstVisitor.h>
#include <MediaItem.h>
#include <Readable.h>
#include <AudioVisual.h>
#include <Article.h>
#include <Book.h>
#include <Film.h>
#include <Podcast.h>
#include <Music.h>

class JsonVisitor : public ConstVisitor {
private:
    QJsonObject object;
public:
    void visit(const MediaItem* media) override;

    void visit(const Readable* readable) override;

    void visit(const AudioVisual* audioVisual) override;

    void visit(const Article* article) override;

    void visit(const Book* book) override;

    void visit(const Film* film) override;

    void visit(const Podcast* podcast) override;

    void visit(const Music* music) override;

    QJsonObject getObject();
};

#endif // JSONVISITOR_H