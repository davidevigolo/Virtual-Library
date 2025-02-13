#include "AudioVisual.h"

AudioVisual::AudioVisual(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, const std::string& format, const std::string& language,
                const std::string& used, const unsigned int duration, const std::string& image) :
                MediaItem(title, author, releaseDate, productionHouse, genre, tags, format, language, used, image), duration(duration) {}

AudioVisual::AudioVisual(MediaItem* media, const unsigned int duration) : MediaItem(*media), duration(duration) {}
            
AudioVisual::~AudioVisual() = default;

unsigned int AudioVisual::getDuration() const {
    return duration;
}

void AudioVisual::setDuration(unsigned int duration) {
    this->duration = duration;
}