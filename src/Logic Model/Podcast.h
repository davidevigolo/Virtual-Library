#ifndef PODCAST_H
#define PODCAST_H

#include "AudioVisual.h"


class Podcast : public AudioVisual {
private:
    unsigned int episode;

public:
    Podcast(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, 
                const std::string& format, const std::string& language, const std::string& used, const unsigned int duration, const unsigned int episode = 0, const std::string& image = "");
    
    ~Podcast();

    unsigned getEpisode() const;

    void setEpisode(unsigned episode);

    void accept(ConstVisitor *visitor) const override;
    void accept(Visitor *visitor) override;
};

#endif // PODCAST_H