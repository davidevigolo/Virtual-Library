#ifndef AUDIOVISUAL_H
#define AUDIOVISUAL_H
#include "MediaItem.h"

class AudioVisual : public MediaItem {
    private:
        std::string duration;
    public:
        AudioVisual(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, 
                const std::string& format, const std::string& language, const std::string& used, const std::string& duration = "", const std::string& image = "");
        AudioVisual(MediaItem* media, const std::string& duration = "") : MediaItem(*media), duration(duration) {};
        virtual ~AudioVisual();

        // Getters
        std::string getDuration() const;
        // Setters
        void setDuration(const std::string& duration);

        void accept(JsonVisitor *visitor)  const override;
        void accept(XmlVisitor *visitor) override;
};

#endif // !AUDIOVISUAL_H