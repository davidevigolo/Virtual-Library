#include <iostream>
#include <../src/Save/json/JsonManager.h>
#include <../src/Logic Model/Article.h>
#include <../src/Logic Model/Book.h>
#include <../src/Logic Model/Film.h>
#include <../src/Logic Model/Music.h>
#include <../src/Logic Model/Podcast.h>
#include <typeinfo>

int main() {
    JsonManager jsonManager("test.json");
    QVector<MediaItem*> objects = jsonManager.readJson();
    if (objects.size() > 1) {
        delete objects[1];
        objects.erase(objects.begin() + 1);
    }
    for (auto obj : objects) {
        std::cout<<obj->getTitle()<<"        ";    
        std::cout<<obj->getAuthor()<<std::endl;
        std::endl(std::cout);
    }
    jsonManager.save(objects);
    return 0;
}