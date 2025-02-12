#ifndef BOOK_H
#define BOOK_H

#include "Readable.h"

class Book : public Readable {
    private:
        unsigned int ISBN;
    public:
        Book(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, 
                const std::string& format, const std::string& language, const std::string& used, const std::string& edition, const unsigned int pages, unsigned int ISBN = 0, const std::string& image = "");
        
        Book(Readable* media, unsigned int ISBN = 0);
        ~Book();
        unsigned int getISBN() const;
        void setISBN(unsigned int ISBN);
        void accept(JsonVisitor *visitor) const override;
        void accept(XmlVisitor *visitor) const override;
};

#endif // !BOOK_H