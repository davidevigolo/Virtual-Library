#include "JsonVisitor.h"
#include "../../Logic Model/MediaItem.h"
#include "../../Logic Model/Readable.h"
#include "../../Logic Model/AudioVisual.h"
#include "../../Logic Model/Article.h"
#include "../../Logic Model/Book.h"
#include "../../Logic Model/Film.h"
#include "../../Logic Model/Podcast.h"
#include "../../Logic Model/Music.h"

void JsonVisitor::visit(const MediaItem* media){
    QJsonObject obj;
    obj["Title"] = media->getTitle().c_str();
    obj["Author"] = media->getAuthor().c_str();
    obj["ReleaseDate"] = media->getReleaseDate().c_str();
    obj["ProductionHouse"] = media->getProductionHouse().c_str();
    obj["Genre"] = media->getGenre().c_str();
    obj["Format"] = media->getFormat().c_str();
    obj["Language"] = media->getLanguage().c_str();
    obj["Used"] = media->getUsed().c_str();
    obj["Image"] = media->getImage().c_str();
    QJsonArray tagsArray;
    for (const std::string& tag : media->getTags()) {
        tagsArray.append(tag.c_str());
    }
    obj["Tags"] = tagsArray;
    object = obj;
}

void JsonVisitor::visit(const Readable* readable){
    visit(static_cast<const MediaItem*>(readable));
    object["Edition"] = readable->getEdition().c_str();
    object["Pages"] = static_cast<int>(readable->getPages());
}

void JsonVisitor::visit(const AudioVisual* audioVisual){
    visit(static_cast<const MediaItem*>(audioVisual));
    object["Duration"] = audioVisual->getDuration().c_str();
    
}

void JsonVisitor::visit(const Article* article){
    visit(static_cast<const Readable*>(article));
    object["Publisher"] = article->getPublisher().c_str();
    object["Class"] = "Article";
    
}

void JsonVisitor::visit(const Book* book){
    visit(static_cast<const Readable*>(book));
    object["ISBN"] = static_cast<int>(book->getISBN());
    object["Class"] = "Book";
    
}

void JsonVisitor::visit(const Film* film){
    visit(static_cast<const AudioVisual*>(film));
    object["Tecnic"] = film->getTecnic().c_str();
    object["Framerate"] = static_cast<int>(film->getFramerate());
    object["Class"] = "Film";
    
}

void JsonVisitor::visit(const Podcast* podcast){
    visit(static_cast<const AudioVisual*>(podcast));
    object["Episodes"] = static_cast<int>(podcast->getEpisodes());
    object["Class"] = "Podcast";
    
}

void JsonVisitor::visit(const Music* music){
    visit(static_cast<const AudioVisual*>(music));
    object["Album"] = music->getAlbum().c_str();
    object["Class"] = "Music";
    
}

QJsonObject JsonVisitor::getObject(){
    return object;
}