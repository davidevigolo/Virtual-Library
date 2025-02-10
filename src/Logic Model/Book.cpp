#include "Book.h"

Book::Book(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, 
                const std::string& format, const std::string& language, const std::string& used, const std::string& edition, const unsigned int& pages, unsigned int ISBN)
                : Readable(title, author, releaseDate, productionHouse, genre, tags, format, language, used, edition, pages), ISBN(ISBN) {}

Book::~Book() {}

unsigned int Book::getISBN() const {
    return ISBN;
}

void Book::setISBN(unsigned int ISBN) {
    this->ISBN = ISBN;
}

QJsonObject Book::accept(JsonVisitor *visitor) {
    return visitor->visit(this);
}