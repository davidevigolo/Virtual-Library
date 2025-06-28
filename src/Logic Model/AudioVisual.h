#ifndef AUDIOVISUAL_H
#define AUDIOVISUAL_H
#include "MediaItem.h"

class AudioVisual : public MediaItem {
    private:
        unsigned int duration; //in seconds
    public:
        AudioVisual(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, 
                const std::string& format, const std::string& language, bool used = false, unsigned int duration = 0, const std::string& image = "");
        virtual ~AudioVisual();

        // Getters
        unsigned int getDuration() const;
        // Setters
        void setDuration(unsigned int duration);

        void accept(ConstVisitor *visitor) const = 0;
        void accept(Visitor *visitor) = 0;
};

#endif // !AUDIOVISUAL_H