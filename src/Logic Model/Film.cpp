#include <Film.h>

// Constructor
Film::Film(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
           const std::string& genre, const std::vector<std::string>& tags, 
           const std::string& format, const std::string& language, const std::string& used, 
           const unsigned int duration, const std::string& tecnic, const double framerate,
           const std::string& director, const std::string& image)
    : AudioVisual(title, author, releaseDate, productionHouse, genre, tags, format, language, used, duration,image),
      tecnic(tecnic), framerate(framerate), director(director) {}

Film::Film(AudioVisual* media, const std::string& tecnic, const double framerate, const std::string& director) : AudioVisual(*media), tecnic(tecnic), framerate(framerate), director(director) {}


// Getters
std::string Film::getTecnic() const {
    return tecnic;
}

std::string Film::getDirector() const {
    return director;
}

double Film::getFramerate() const {
    return framerate;
}

// Setters
void Film::setTecnica(const std::string& tecnic) {
    this->tecnic = tecnic;
}

void Film::setFramerate(double framerate) {
    this->framerate = framerate;
}

void Film::setDirector(const std::string& director) {
    this->director = director;
}


void Film::accept(JsonVisitor *visitor) const{
    visitor->visit(this);
}

void Film::accept(XmlVisitor *visitor) const{
    visitor->visit(this);
}