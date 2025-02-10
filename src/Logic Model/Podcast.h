#ifndef PODCAST_H
#define PODCAST_H

#include "AudioVisual.h"


class Podcast : public AudioVisual {
private:
    unsigned int episodes;

public:
    Podcast(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, 
                const std::string& format, const std::string& language, const std::string& used, const std::string& duration, unsigned int episodes = 0, const std::string& image = "");

    ~Podcast();

    unsigned getEpisodes() const;

    void setEpisodes(unsigned episodes);

    void accept(JsonVisitor *visitor) const override;
};

#endif // PODCAST_H