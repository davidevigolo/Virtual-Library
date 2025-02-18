#include "Readable.h"

Readable::Readable(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, 
                const std::string& format, const std::string& language, const std::string& used, const std::string& edition, const unsigned int pages, const std::string& image):
                MediaItem(title, author, releaseDate, productionHouse, genre, tags, format, language, used,image), edition(edition), pages(pages) {}
Readable::Readable(MediaItem* media, const std::string& edition, unsigned int pages) : MediaItem(*media), edition(edition), pages(pages) {}
Readable::~Readable() = default;

std::string Readable::getEdition() const {
    return edition;
}

unsigned int Readable::getPages() const {
    return pages;
}

void Readable::setEdition(const std::string& edition) {
    this->edition = edition;
}

void Readable::setPages(unsigned int pages) {
    this->pages = pages;
}