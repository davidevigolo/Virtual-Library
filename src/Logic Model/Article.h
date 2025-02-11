#ifndef ARTICLE_H
#define ARTICLE_H
#include "Readable.h"

class Article : public Readable{
    private:
        std::string publisher;
    public:
        Article(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, 
                const std::string& format, const std::string& language, const std::string& used, const std::string edition, const unsigned int& pages, const std::string& publisher = "");
        Article(Readable* media, const std::string& publisher = "") : Readable(*media), publisher(publisher) {};
        virtual ~Article();

        // Getters
        std::string getPublisher() const;
        // Setters
        void setPublisher(const std::string& publisher);

        QJsonObject accept(JsonVisitor *visitor) override;
        void accept(XmlVisitor *visitor) override;
};
#endif // !ARTICLE_H