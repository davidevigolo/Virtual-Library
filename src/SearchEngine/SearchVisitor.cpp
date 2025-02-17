#include <SearchVisitor.h>
#include <iostream>

SearchVisitor::SearchVisitor(const QString& query) : query(query), points(0), pointsValue{
        {"Title", 10},//mediaItem
        {"Author", 5},
        {"Release Date", 5},
        {"Production House", 5},
        {"Genre", 5},
        {"Tags", 5},
        
        {"Edition", 5},//Readable
        
        {"Publisher", 5},//Article

        {"ISBN", 5},//Book
        
        {"Duration", 5},//AudioVisual
        
        {"Director", 5},//Film
        {"Tecnic", 5},
        
        {"Album", 5},//Music
        
        {"Episode", 5}//Podcast
    } {};

int SearchVisitor::getPoints() const {
    return points;
}

void SearchVisitor::visit(const MediaItem* item) {
    points = 0;
    if (item->getTitle().find(query.toStdString()) != std::string::npos) {
        points += pointsValue["Title"];
    }
    if (item->getAuthor().find(query.toStdString()) != std::string::npos) {
        points += pointsValue["Author"];
    }
    if (item->getReleaseDate().find(query.toStdString()) != std::string::npos) {
        points += pointsValue["Release Date"];
    }
    if (item->getProductionHouse().find(query.toStdString()) != std::string::npos) {
        points += pointsValue["Production House"];
    }
    if (item->getGenre().find(query.toStdString()) != std::string::npos) {
        points += pointsValue["Genre"];
    }
    for (const auto& tag : item->getTags()) {
        if (tag.find(query.toStdString()) != std::string::npos) {
            points += pointsValue["Tags"];
        }
    }
}

void SearchVisitor::visit(const Readable* item) {
    visit(static_cast<const MediaItem*>(item));
    if (item->getEdition().find(query.toStdString()) != std::string::npos) {
        points += pointsValue["Edition"];
    }
}

void SearchVisitor::visit(const AudioVisual* item){
    visit(static_cast<const MediaItem*>(item));
    if (std::to_string(item->getDuration()).find(query.toStdString()) != std::string::npos) {
        points += pointsValue["Duration"];
    }
}

void SearchVisitor::visit(const Article* item) {
    visit(static_cast<const Readable*>(item));
    if (item->getPublisher().find(query.toStdString()) != std::string::npos) {
        points += pointsValue["Publisher"];
    }
}

void SearchVisitor::visit(const Book* item) {
    visit(static_cast<const Readable*>(item));
    if (std::to_string(item->getISBN()).find(query.toStdString()) != std::string::npos) {
        points += pointsValue["ISBN"];
    }
}

void SearchVisitor::visit(const Film* item) {
    visit(static_cast<const AudioVisual*>(item));
    if (item->getDirector().find(query.toStdString()) != std::string::npos) {
        points += pointsValue["Director"];
    }
    if (item->getTecnic().find(query.toStdString()) != std::string::npos) {
        points += pointsValue["Tecnic"];
    }
}

void SearchVisitor::visit(const Podcast* item) {
    visit(static_cast<const AudioVisual*>(item));
    if (std::to_string(item->getEpisode()).find(query.toStdString()) != std::string::npos) {
        points += pointsValue["Episode"];
    }
}

void SearchVisitor::visit(const Music* item) {
    visit(static_cast<const AudioVisual*>(item));
    if (item->getAlbum().find(query.toStdString()) != std::string::npos) {
        points += pointsValue["Album"];
    }
}