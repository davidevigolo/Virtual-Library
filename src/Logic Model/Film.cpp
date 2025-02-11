#include "Film.h"

// Constructor
Film::Film(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
           const std::string& genre, const std::vector<std::string>& tags, 
           const std::string& format, const std::string& language, const std::string& used, 
           const std::string& duration, const std::string& tecnic, const double framerate,
           const std::string& director)
    : AudioVisual(title, author, releaseDate, productionHouse, genre, tags, format, language, used, duration),
      tecnic(tecnic), framerate(framerate), director(director) {}

// Destructor
Film::~Film() {}

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


QJsonObject Film::accept(JsonVisitor *visitor) {
    return visitor->visit(this);
}

void Film::accept(XmlVisitor *visitor) {
    visitor->visit(this);
}