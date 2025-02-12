#include "XmlVisitor.h"
#include "MediaItem.h"
#include "Book.h"
#include "Film.h"
#include "Readable.h"
#include "Article.h"
#include "AudioVisual.h"
#include "Podcast.h"
#include "Music.h"

void XmlVisitor::visit(const MediaItem* media, bool onlyBody){
    if(!onlyBody) writer.writeStartElement("MediaItem");
    writer.writeTextElement("Title", media->getTitle().c_str());
    writer.writeTextElement("Author", media->getAuthor().c_str());
    writer.writeTextElement("ReleaseDate", media->getReleaseDate().c_str());
    writer.writeTextElement("ProductionHouse", media->getProductionHouse().c_str());
    writer.writeTextElement("Genre", media->getGenre().c_str());
    writer.writeStartElement("Tags");
    for (const std::string& tag : media->getTags()) {
        writer.writeTextElement("Tag", tag.c_str());
    }
    writer.writeEndElement();
    writer.writeTextElement("Format", media->getFormat().c_str());
    writer.writeTextElement("Language", media->getLanguage().c_str());
    writer.writeTextElement("Used", media->getUsed().c_str());
    if (!onlyBody) writer.writeEndElement();
}

void XmlVisitor::visit(const Readable* media, bool onlyBody){
    if(!onlyBody) writer.writeStartElement("Readable");
    visit(static_cast<const MediaItem*>(media), true);
    writer.writeTextElement("Edition", media->getEdition().c_str());
    writer.writeTextElement("Pages", std::to_string(media->getPages()).c_str());
    if (!onlyBody) writer.writeEndElement();
}

void XmlVisitor::visit(const Book* media, bool onlyBody){
    if(!onlyBody) writer.writeStartElement("Book");
    visit(static_cast<const Readable*>(media), true);
    writer.writeTextElement("ISBN", std::to_string(media->getISBN()).c_str());
    if (!onlyBody) writer.writeEndElement();
}

void XmlVisitor::visit(const Article* media, bool onlyBody){
    if(!onlyBody) writer.writeStartElement("Article");
    visit(static_cast<const Readable*>(media), true);
    writer.writeTextElement("Publisher", media->getPublisher().c_str());
    if (!onlyBody) writer.writeEndElement();
}

void XmlVisitor::visit(const AudioVisual* media, bool onlyBody){
    if(!onlyBody) writer.writeStartElement("AudioVisual");
    visit(static_cast<const MediaItem*>(media), true);
    writer.writeTextElement("Duration", std::to_string(media->getDuration()).c_str());
    if (!onlyBody) writer.writeEndElement();
}

void XmlVisitor::visit(const Film* media, bool onlyBody){
    if(!onlyBody) writer.writeStartElement("Film");
    visit(static_cast<const AudioVisual*>(media), true);
    writer.writeTextElement("Tecnic", media->getTecnic().c_str());
    writer.writeTextElement("Framerate", std::to_string(media->getFramerate()).c_str());
    writer.writeTextElement("Director", media->getDirector().c_str());
    if (!onlyBody) writer.writeEndElement();
}

void XmlVisitor::visit(const Podcast* media, bool onlyBody){
    if(!onlyBody) writer.writeStartElement("Podcast");
    visit(static_cast<const AudioVisual*>(media), true);
    writer.writeTextElement("Episodes", std::to_string(media->getEpisodes()).c_str());
    if (!onlyBody) writer.writeEndElement();
}

void XmlVisitor::visit(const Music* media, bool onlyBody){
    if(!onlyBody) writer.writeStartElement("Music");
    visit(static_cast<const AudioVisual*>(media), true);
    writer.writeTextElement("Album", media->getAlbum().c_str());
    if (!onlyBody) writer.writeEndElement();
}