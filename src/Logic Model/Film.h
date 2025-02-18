#ifndef FILM_H
#define FILM_H

#include "AudioVisual.h"


class Film : public AudioVisual {
private:
    std::string technique;
    double framerate;
    std::string director;
public:
    Film(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
         const std::string& genre, const std::vector<std::string>& tags, 
         const std::string& format, const std::string& language, const std::string& used, 
         const unsigned int duration, const std::string& technique, const double framerate,
         const std::string& director, const std::string& image = "");

    //Getters
    std::string getTechnique() const;
    std::string getDirector() const;
    double getFramerate() const;

    //Setters
    void setTechnique(const std::string& tecnica);
    void setFramerate(double framerate);
    void setDirector(const std::string& director);

    void accept(ConstVisitor *visitor) const override;
    void accept(Visitor *visitor) override;
};

#endif // FILM_H