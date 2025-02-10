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
    std::vector<std::pair<std::string,std::string>> changes = {{"Title", "ChangedTitle"},{ "Author", "ChangedAuthor"}};
    //jsonManager.ModifyObject(objects[1], changes);
    for (auto obj : objects) {
        std::cout<<obj->getTitle()<<"        ";    
        std::cout<<obj->getAuthor()<<std::endl;
        std::endl(std::cout);
    }
    return 0;
}