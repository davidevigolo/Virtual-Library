#ifndef READABLE_H
#define READABLE_H
#include "MediaItem.h"

class Readable : public MediaItem {
    private:
        std::string edition;
        unsigned int pages;
    public:
        Readable(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, 
                const std::string& format, const std::string& language, const std::string& used, const std::string& edition = "", const unsigned int& pages = 0);
        virtual ~Readable();

        // Getters
        std::string getEdition() const;
        unsigned int getPages() const;
        // Setters
        void setEdition(const std::string& edition);
        void setPages(const unsigned int& pages);

        QJsonObject accept(JsonVisitor *visitor) override;
        
};;


#endif // !READABLE_H
