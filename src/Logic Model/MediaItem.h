#ifndef MEDIAITEM_H
#define MEDIAITEM_H

#include <string>
#include <vector>
#include <Visitor.h>
#include <ConstVisitor.h>

class MediaItem {
    private:
        std::string title;
        std::string author;
        std::string releaseDate;
        std::string productionHouse;
        std::string genre;
        std::vector<std::string> tags;
        std::string format;//phisical/digital
        std::string language;
        bool used;
        std::string image;
    public:
        MediaItem(const std::string& title  = "",const std::string& author = "", const std::string& releaseDate = "", const std::string& productionHouse = "", 
                const std::string& genre = "", const std::vector<std::string>& tags = {""}, 
                const std::string& format = "", const std::string& language = "", bool used = false, const std::string& image = "");
        
        virtual ~MediaItem();

        // Getters
        std::string getTitle() const;
        std::string getAuthor() const;
        std::string getReleaseDate() const;
        std::string getProductionHouse() const;
        std::string getGenre() const;
        std::vector<std::string> getTags() const;
        std::string getFormat() const;
        std::string getLanguage() const;
        bool getUsed() const;
        std::string getImage() const;
        // Setters
        void setTitle(const std::string& title);
        void setAuthor(const std::string& author);
        void setReleaseDate(const std::string& releaseDate);
        void setProductionHouse(const std::string& productionHouse);
        void setGenre(const std::string& genre);
        void setTags(const std::vector<std::string>& tags);
        void setFormat(const std::string& format);
        void setLanguage(const std::string& language);
        void setUsed(bool used);
        void setImage(const std::string& image);

        virtual void accept(ConstVisitor *visitor) const = 0;
        virtual void accept(Visitor *visitor) = 0;


};

#endif // MEDIAITEM_H