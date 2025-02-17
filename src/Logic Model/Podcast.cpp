#include "Podcast.h"

Podcast::Podcast(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                 const std::string& genre, const std::vector<std::string>& tags, 
                 const std::string& format, const std::string& language, const std::string& used, const unsigned int duration, const unsigned int episode, const std::string& image)
    : AudioVisual(title, author, releaseDate, productionHouse, genre, tags, format, language, used, duration,image), episode(episode) {}
Podcast::Podcast(AudioVisual* media, unsigned int episode) : AudioVisual(*media), episode(episode) {}
Podcast::~Podcast() {}

unsigned Podcast::getEpisode() const {
    return episode;
}

void Podcast::setEpisode(unsigned episode) {
    this->episode = episode;
}

void Podcast::accept(ConstVisitor *visitor) const{
    visitor->visit(this);
}

void Podcast::accept(Visitor *visitor) {
    visitor->visit(this);
}