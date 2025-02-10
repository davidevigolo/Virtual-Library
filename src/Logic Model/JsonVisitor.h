#ifndef JSONVISITOR_H
#define JSONVISITOR_H

#include "Visitor.h"

class JsonVisitor : public Visitor {
public:
    QJsonObject visit(MediaItem* media);

    QJsonObject visit(Readable* readable);

    QJsonObject visit(AudioVisual* audioVisual);

    QJsonObject visit(Article* article);

    QJsonObject visit(Book* book);

    QJsonObject visit(Film* film);

    QJsonObject visit(Podcast* podcast);

    QJsonObject visit(Music* music);
};

#endif // JSONVISITOR_H