#include "MediaItem.h"

MediaItem::MediaItem(const std::string& title, const std::string& author, const std::string& releaseDate, const std::string& productionHouse, 
                const std::string& genre, const std::vector<std::string>& tags, 
                const std::string& format, const std::string& language, const std::string& used, const std::string& image):
                title(title), author(author), releaseDate(releaseDate), productionHouse(productionHouse), genre(genre),
                tags(tags), format(format), language(language), used(used), image(image) {}

MediaItem::~MediaItem() = default;

std::string MediaItem::getTitle() const {
    return title;
}

std::string MediaItem::getAuthor() const {
    return author;
}

std::string MediaItem::getReleaseDate() const {
    return releaseDate;
}

std::string MediaItem::getProductionHouse() const {
    return productionHouse;
}

std::string MediaItem::getGenre() const {
    return genre;
}

std::vector<std::string> MediaItem::getTags() const {
    return tags;
}

std::string MediaItem::getFormat() const {
    return format;
}

std::string MediaItem::getLanguage() const {
    return language;
}

std::string MediaItem::getStatus() const {
    return used;
}

std::string MediaItem::getUsed() const {
    return used;
}

std::string MediaItem::getImage() const {
    return image;
}

void MediaItem::setTitle(const std::string& title) {
    this->title = title;
}

void MediaItem::setAuthor(const std::string& author) {
    this->author = author;
}

void MediaItem::setReleaseDate(const std::string& releaseDate) {
    this->releaseDate = releaseDate;
}

void MediaItem::setProductionHouse(const std::string& productionHouse) {
    this->productionHouse = productionHouse;
}

void MediaItem::setGenre(const std::string& genre) {
    this->genre = genre;
}

void MediaItem::setTags(const std::vector<std::string>& tags) {
    this->tags = tags;
}

void MediaItem::setFormat(const std::string& format) {
    this->format = format;
}

void MediaItem::setStatus(const std::string& used) {
    this->used = used;
}

void MediaItem::setLanguage(const std::string& language) {
    this->language = language;
}

void MediaItem::setUsed(const std::string& used) {
    this->used = used;
}

void MediaItem::setImage(const std::string& image) {
    this->image = image;
}

void MediaItem::accept(JsonVisitor* visitor)const {
    visitor->visit(this);
}

