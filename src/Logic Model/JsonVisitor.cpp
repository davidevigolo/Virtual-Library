#include "JsonVisitor.h"
#include "MediaItem.h"
#include "Readable.h"
#include "AudioVisual.h"
#include "Article.h"
#include "Book.h"
#include "Film.h"
#include "Podcast.h"
#include "Music.h"

QJsonObject JsonVisitor::visit(MediaItem* media){
    QJsonObject obj;
    obj["Title"] = media->getTitle().c_str();
    obj["Author"] = media->getAuthor().c_str();
    obj["ReleaseDate"] = media->getReleaseDate().c_str();
    obj["ProductionHouse"] = media->getProductionHouse().c_str();
    obj["Genre"] = media->getGenre().c_str();
    obj["Format"] = media->getFormat().c_str();
    obj["Language"] = media->getLanguage().c_str();
    obj["Used"] = media->getUsed().c_str();
    QJsonArray tagsArray;
    for (const std::string& tag : media->getTags()) {
        tagsArray.append(tag.c_str());
    }
    obj["Tags"] = tagsArray;
    return obj;
}

QJsonObject JsonVisitor::visit(Readable* readable){
    QJsonObject obj = visit(static_cast<MediaItem*>(readable));
    obj["Edition"] = readable->getEdition().c_str();
    obj["Pages"] = static_cast<int>(readable->getPages());
    return obj;
}

QJsonObject JsonVisitor::visit(AudioVisual* audioVisual){
    QJsonObject obj = visit(static_cast<MediaItem*>(audioVisual));
    obj["Duration"] = audioVisual->getDuration().c_str();
    return obj;
}

QJsonObject JsonVisitor::visit(Article* article){
    QJsonObject obj = visit(static_cast<Readable*>(article));
    obj["Publisher"] = article->getPublisher().c_str();
    obj["Class"] = "Article";
    return obj;
}

QJsonObject JsonVisitor::visit(Book* book){
    QJsonObject obj = visit(static_cast<Readable*>(book));
    obj["ISBN"] = static_cast<int>(book->getISBN());
    obj["Class"] = "Book";
    return obj;
}

QJsonObject JsonVisitor::visit(Film* film){
    QJsonObject obj = visit(static_cast<AudioVisual*>(film));
    obj["Tecnic"] = film->getTecnic().c_str();
    obj["Framerate"] = static_cast<int>(film->getFramerate());
    obj["Class"] = "Film";
    return obj;
}

QJsonObject JsonVisitor::visit(Podcast* podcast){
    QJsonObject obj = visit(static_cast<AudioVisual*>(podcast));
    obj["Episodes"] = static_cast<int>(podcast->getEpisodes());
    obj["Class"] = "Podcast";
    return obj;
}

QJsonObject JsonVisitor::visit(Music* music){
    QJsonObject obj = visit(static_cast<AudioVisual*>(music));
    obj["Album"] = music->getAlbum().c_str();
    obj["Class"] = "Music";
    return obj;
}