#include <iostream>
#include <vector>
#include <QFile>
#include <JsonManager.h>
#include <MediaItem.h>
#include <Book.h>
#include <Article.h>
#include <Film.h>
#include <Podcast.h>
#include <Music.h>
#include <AudioVisual.h>
#include <Readable.h>
#include "JsonTest.h"

void JsonManagerTest::testSaveAndLoadMediaItems() {
    JsonManager jsonManager("test.json");
    QVector<MediaItem*> mediaItems;

    // Create some test media items
    std::vector<std::string> tags = {"Classic", "Fiction"};
    Book* book = new Book(std::string("The Great Gatsby"), std::string("F. Scott Fitzgerald"), std::string("1925"), std::string("Scribner"), std::string("Classic"), tags, std::string("Paperback"), std::string("English"), false, std::string("First"), 180, 978074u);
    Article* article = new Article(std::string("The Great Gatsby"), std::string("F. Scott Fitzgerald"), std::string("1925"), std::string("Scribner"), std::string("Classic"), tags, std::string("Paperback"), std::string("English"), false, std::string("First"), 180, std::string("The New York Times"));
    Film* film = new Film(std::string("Mannaggia"), std::string("Aldo Giovanni e Jack"), std::string("1999"), std::string("Medusa"), std::string("Comedy"), tags, std::string("DVD"), std::string("Italian"), false, 120, std::string("Digital"), 24, std::string("Aldo Giovanni e Jack"));
    Podcast* podcast = new Podcast(std::string("Mannaggia"), std::string("Aldo Giovanni e Jack"), std::string("1999"), std::string("Medusa"), std::string("Comedy"), tags, std::string("DVD"), std::string("Italian"), false, 120, 24);
    Music* music = new Music(std::string("Mannaggia"), std::string("Aldo Giovanni e Jack"), std::string("1999"), std::string("Medusa"), std::string("Comedy"), tags, std::string("DVD"), std::string("Italian"), false, 120, std::string("Aldo Giovanni e Jack"));
    
    mediaItems.push_back(book);
    mediaItems.push_back(article);
    mediaItems.push_back(film);
    mediaItems.push_back(podcast);
    mediaItems.push_back(music);

    // Save the media items to an XML file
    jsonManager.save(mediaItems);

    // // Load the media items from the XML file
    QVector<MediaItem*> loadedMediaItems = jsonManager.load();
    std::cout << loadedMediaItems.size() << std::endl;

    // Verify that the loaded media items match the original media items
    if (mediaItems.size() != loadedMediaItems.size()) {
        std::cerr << "Test failed: size mismatch" << std::endl;
        return;
    }

    for (int i = 0; i < mediaItems.size(); ++i) {
        if (mediaItems[i]->getTitle() != loadedMediaItems[i]->getTitle() ||
            mediaItems[i]->getAuthor() != loadedMediaItems[i]->getAuthor() ||
            mediaItems[i]->getReleaseDate() != loadedMediaItems[i]->getReleaseDate() ||
            mediaItems[i]->getProductionHouse() != loadedMediaItems[i]->getProductionHouse() ||
            mediaItems[i]->getGenre() != loadedMediaItems[i]->getGenre() ||
            mediaItems[i]->getTags() != loadedMediaItems[i]->getTags() ||
            mediaItems[i]->getFormat() != loadedMediaItems[i]->getFormat() ||
            mediaItems[i]->getLanguage() != loadedMediaItems[i]->getLanguage() ||
            mediaItems[i]->getUsed() != loadedMediaItems[i]->getUsed()) {
            std::cerr << "Test failed: data mismatch" << std::endl;
            return;
        }
    }

    std::cout << "Test passed" << std::endl;

    // Clean up
    for (MediaItem* item : mediaItems) {
        delete item;
    }
    for (MediaItem* item : loadedMediaItems) {
        delete item;
    }
}