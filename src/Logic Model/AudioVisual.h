#ifndef AUDIOVISUAL_H
#define AUDIOVISUAL_H
#include "MediaItem.h"

class AudioVisual : public MediaItem {
    private:
        unsigned int duration; //in seconds
    public:
        AudioVisual(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, 
                const std::string& format, const std::string& language, const std::string& used, const unsigned int duration = 0, const std::string& image = "");
        AudioVisual(MediaItem* media, const unsigned int duration = 0);
        virtual ~AudioVisual();

        // Getters
        unsigned int getDuration() const;
        // Setters
        void setDuration(unsigned int duration);

        void accept(JsonVisitor *visitor)  const override;
        void accept(XmlVisitor *visitor) const override;
};

#endif // !AUDIOVISUAL_H