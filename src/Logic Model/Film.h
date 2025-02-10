#ifndef FILM_H
#define FILM_H

#include "AudioVisual.h"


class Film : public AudioVisual {
private:
    std::string tecnic;
    double framerate;
    std::string director;

public:
    Film(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
         const std::string& genre, const std::vector<std::string>& tags, 
         const std::string& format, const std::string& language, const std::string& used, 
         const std::string& duration, const std::string& tecnic, const double framerate,
         const std::string& director);

    ~Film();

    //Getters
    std::string getTecnic() const;
    std::string getDirector() const;
    double getFramerate() const;

    //Setters
    void setTecnica(const std::string& tecnica);
    void setFramerate(double framerate);
    void setDirector(const std::string& director);

    QJsonObject accept(JsonVisitor *visitor) override;
};

#endif // FILM_H