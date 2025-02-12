#ifndef JSONVISITOR_H
#define JSONVISITOR_H

#include "../../Logic Model/Visitor.h"

class JsonVisitor : public Visitor {
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