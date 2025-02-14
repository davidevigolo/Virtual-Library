#include <iostream>
#include "../src/Save/json/JsonManager.h"
#include "../src/Logic Model/Article.h"
#include "../src/Logic Model/Book.h"
#include "../src/Logic Model/Film.h"
#include "../src/Logic Model/Music.h"
#include "../src/Logic Model/Podcast.h"
#include "typeinfo"
#include "XmlManagerTest.h"
#include "jsonTests/JsonTest.h"
#include "GUITests/MainWindowTests/LoadFromFileTests.h"

int main() {
    // JsonManagerTest::testSaveAndLoadMediaItems();
    qDebug() << "JsonManagerTest::testSaveAndLoadMediaItems()";
    XmlManagerTest::testSaveAndLoadMediaItems();

    // std::cout<<"\n\n\n\nPORCODIO\n\n\n\n";
    // assert(LoadFromFileTest::testLoadFromFile() == 0);
}