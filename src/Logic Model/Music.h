#ifndef MUSIC_H
#define MUSIC_H
#include "AudioVisual.h"


class  Music : public AudioVisual {
    private:
        std::string album;
    public:
        Music(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, 
                const std::string& format, const std::string& language, const std::string& used, const std::string& duration, const std::string& album = "");
        virtual ~Music();

        // Getters
        std::string getAlbum() const;
        // Setters
        void setAlbum(const std::string& album);

        QJsonObject accept(JsonVisitor *visitor) override;
};

#endif // !MUSIC_H