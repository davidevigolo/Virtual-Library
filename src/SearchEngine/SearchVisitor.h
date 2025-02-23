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

/**
    * @brief SearchVisitor is a class that is used to give items a score 
    * based on how well they match a search query based on weights given to the various fields of an item
*/

class SearchVisitor : public ConstVisitor {
private:
    int points;
    QString query;
    std::map<std::string,int> pointsValue;
    bool compare(std::string str1, QString str2);
public:
    SearchVisitor(const QString& query, std::map<std::string,int> pointsValue);
    virtual void visit(const MediaItem* media) override;
    virtual void visit(const Readable* readable) override;
    virtual void visit(const AudioVisual* audioVisual) override;
    virtual void visit(const Article* articles) override;
    virtual void visit(const Book* book) override;
    virtual void visit(const Film* film) override;
    virtual void visit(const Podcast* podcast) override;
    virtual void visit(const Music* music) override;
    bool is_number(const std::string& s);
    QString getQuery() const;
    std::map<std::string,int> getWeight() const;
    void setWeight(std::map<std::string,int> newWeight);
    void setQuery(const QString &query);
    int getPoints() const;
};