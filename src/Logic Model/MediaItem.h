#ifndef MEDIAITEM_H
#define MEDIAITEM_H

#include <string>
#include <vector>
#include "../Save/json/JsonVisitor.h"

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
        std::string used;//like seen =  read, etc
        std::string image;
    public:
        MediaItem(const std::string& title  = "",const std::string& author = "", const std::string& releaseDate = "", const std::string& productionHouse = "", 
                const std::string& genre = "", const std::vector<std::string>& tags = {""}, 
                const std::string& format = "", const std::string& language = "", const std::string& used = "", const std::string& image = "");
        virtual ~MediaItem();

        // Getters
        std::string getTitle() const;
        std::string getAuthor() const;
        std::string getReleaseDate() const;
        std::string getProductionHouse() const;
        std::string getGenre() const;
        std::string getStatus() const;
        std::vector<std::string> getTags() const;
        std::string getFormat() const;
        std::string getLanguage() const;
        std::string getUsed() const;
        std::string getImage() const;
        // Setters
        void setTitle(const std::string& title);
        void setAuthor(const std::string& author);
        void setReleaseDate(const std::string& releaseDate);
        void setProductionHouse(const std::string& productionHouse);
        void setGenre(const std::string& genre);
        void setStatus(const std::string& status);
        void setTags(const std::vector<std::string>& tags);
        void setFormat(const std::string& format);
        void setLanguage(const std::string& language);
        void setUsed(const std::string& used);
        void setImage(const std::string& image);

        virtual void accept(JsonVisitor *visitor) const;


};

#endif // MEDIAITEM_H