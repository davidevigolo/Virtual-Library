#include "AudioVisual.h"

AudioVisual::AudioVisual(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, const std::string& format, const std::string& language,
                const std::string& used, const std::string& duration) :
                MediaItem(title, author, releaseDate, productionHouse, genre, tags, format, language, used), duration(duration) {}
            
AudioVisual::~AudioVisual() = default;

std::string AudioVisual::getDuration() const {
    return duration;
}

void AudioVisual::setDuration(const std::string& duration) {
    this->duration = duration;
}

QJsonObject AudioVisual::accept(JsonVisitor *visitor) {
    return visitor->visit(this);
}