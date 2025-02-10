#include "Podcast.h"

Podcast::Podcast(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                 const std::string& genre, const std::vector<std::string>& tags, 
                 const std::string& format, const std::string& language, const std::string& used, const std::string& duration, unsigned int episodes, const std::string& image)
    : AudioVisual(title, author, releaseDate, productionHouse, genre, tags, format, language, used, duration,image), episodes(episodes) {}

Podcast::~Podcast() {}

unsigned Podcast::getEpisodes() const {
    return episodes;
}

void Podcast::setEpisodes(unsigned episodes) {
    this->episodes = episodes;
}

void Podcast::accept(JsonVisitor *visitor) const{
    visitor->visit(this);
}