#include <Film.h>

// Constructor
Film::Film(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
           const std::string& genre, const std::vector<std::string>& tags, 
           const std::string& format, const std::string& language, const bool used, 
           const unsigned int duration, const std::string& technique, const double framerate,
           const std::string& director, const std::string& image)
    : AudioVisual(title, author, releaseDate, productionHouse, genre, tags, format, language, used, duration,image),
      technique(technique), framerate(framerate), director(director) {}

// Getters
std::string Film::getTechnique() const {
    return technique;
}

std::string Film::getDirector() const {
    return director;
}

double Film::getFramerate() const {
    return framerate;
}

// Setters
void Film::setTechnique(const std::string& tecnic) {
    this->technique = tecnic;
}

void Film::setFramerate(double framerate) {
    this->framerate = framerate;
}

void Film::setDirector(const std::string& director) {
    this->director = director;
}


void Film::accept(ConstVisitor *visitor) const{
    visitor->visit(this);
}

void Film::accept(Visitor *visitor) {
    visitor->visit(this);
}