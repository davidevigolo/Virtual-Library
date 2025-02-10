#include "Music.h"

Music::Music(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, 
                const std::string& format, const std::string& language, const std::string& used, const std::string& duration, const std::string& album, const std::string& image) :
                AudioVisual(title, author, releaseDate, productionHouse, genre, tags, format, language, used, duration,image), album(album) {}

Music::~Music() {}

std::string Music::getAlbum() const {
    return album;
}

void Music::setAlbum(const std::string& album) {
    this->album = album;
}

void Music::accept(JsonVisitor *visitor) const{
    visitor->visit(this);
}