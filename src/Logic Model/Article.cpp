#include "Article.h"

Article::Article(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, 
                const std::string& format, const std::string& language, const std::string& used, const std::string edition, const unsigned int& pages, const std::string& publisher, const std::string& image):
                Readable(title, author, releaseDate, productionHouse, genre, tags, format, language, used, edition, pages, image), publisher(publisher) {}

Article::~Article() {}

std::string Article::getPublisher() const {
    return publisher;
}

void Article::setPublisher(const std::string& publisher) {
    this->publisher = publisher;
}

void Article::accept(JsonVisitor *visitor) const {
    visitor->visit(this);
}

void Article::accept(XmlVisitor *visitor) {
    visitor->visit(this);
}