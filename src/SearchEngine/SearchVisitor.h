#pragma once
#include <ConstVisitor.h>
#include <QString>
#include <Article.h>
#include <Book.h>
#include <Film.h>
#include <Podcast.h>
#include <Music.h>
#include <vector>
#include <string>
#include <map>

class SearchVisitor : public ConstVisitor {
private:
    int points;
    QString query;
    std::map<std::string,int> pointsValue;
public:
    SearchVisitor(const QString& query);
    virtual void visit(const MediaItem* media) override;
    virtual void visit(const Readable* readable) override;
    virtual void visit(const AudioVisual* audioVisual) override;
    virtual void visit(const Article* articles) override;
    virtual void visit(const Book* book) override;
    virtual void visit(const Film* film) override;
    virtual void visit(const Podcast* podcast) override;
    virtual void visit(const Music* music) override;
    int getPoints() const;
};