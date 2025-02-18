# Virtual-Library.pro

QT += core gui
QT += widgets
QT += xml

CONFIG += c++20

TARGET = Virtual-Library
TEMPLATE = app

CONFIG += console c++11
CONFIG += debug
CONFIG -= release

INCLUDEPATH += "./src/Logic Model"
INCLUDEPATH += "./src/Save/xml"
INCLUDEPATH += "./src/Save/json"
INCLUDEPATH += "./Test/XmlTests"
INCLUDEPATH += "./src/GUI"
INCLUDEPATH += "./src/GUI/MainDisplay"
INCLUDEPATH += "./src/Save"
INCLUDEPATH += "./src/GUI/Menu"
INCLUDEPATH += "./src/GUI/SearchBar"
INCLUDEPATH += "./src/GUI/ObjectDisplay"
INCLUDEPATH += "./src/SearchEngine"

#SEARCH ENGINE
HEADERS += "./src/SearchEngine/SearchEngine.h"
SOURCES += "./src/SearchEngine/SearchVisitor.h"

SOURCES += "./src/SearchEngine/SearchEngine.cpp"
SOURCES += "./src/SearchEngine/SearchVisitor.cpp"


#GUI 
HEADERS += "./src/GUI/MainWindow.h"
HEADERS += "./src/GUI/MainDisplay/ScrollPanel.h"
HEADERS += "./src/GUI/MainDisplay/CustomScrollArea.h"
HEADERS += "./src/GUI/LoadVisitor.h"
HEADERS += "./src/GUI/MainDisplay/MainDisplay.h"
HEADERS += "./src/GUI/MainDisplay/ButtonWidget.h"
HEADERS += "./src/GUI/Menu/TopMenu.h"
HEADERS += "./src/GUI/SearchBar/SearchBar.h"
HEADERS += "./src/GUI/MainDisplay/ScrollWidget.h"
HEADERS += "./src/GUI/ObjectDisplay/FieldWidget.h"
HEADERS += "./src/GUI/ObjectDisplay/GridVisitor.h"
HEADERS += "./src/GUI/ObjectDisplay/ItemDisplay.h"

SOURCES += "./src/GUI/MainWindow.cpp"
SOURCES += "./src/GUI/MainDisplay/ScrollPanel.cpp"
SOURCES += "./src/GUI/MainDisplay/CustomScrollArea.cpp"
SOURCES += "./src/GUI/LoadVisitor.cpp"
SOURCES += "./src/GUI/MainDisplay/MainDisplay.cpp"
SOURCES += "./src/GUI/MainDisplay/ButtonWidget.cpp"
SOURCES += "./src/GUI/Menu/TopMenu.cpp"
SOURCES += "./src/GUI/SearchBar/SearchBar.cpp"
SOURCES += "./src/GUI/MainDisplay/ScrollWidget.cpp"
SOURCES += "./src/GUI/ObjectDisplay/FieldWidget.cpp"
SOURCES += "./src/GUI/ObjectDisplay/GridVisitor.cpp"
SOURCES += "./src/GUI/ObjectDisplay/ItemDisplay.cpp"

# Logic Model
SOURCES += "./src/Logic Model/MediaItem.cpp"
SOURCES += "./src/Logic Model/AudioVisual.cpp"
SOURCES += "./src/Logic Model/Readable.cpp"
SOURCES += "./src/Logic Model/Article.cpp"
SOURCES += "./src/Logic Model/Book.cpp"
SOURCES += "./src/Logic Model/Film.cpp"
SOURCES += "./src/Logic Model/Music.cpp"
SOURCES += "./src/Logic Model/Podcast.cpp"
SOURCES += "./Test/XmlTests/XmlManagerTest.cpp"
SOURCES += "./src/Save/json/JsonVisitor.cpp"
SOURCES += "./src/Save/xml/XmlVisitor.cpp"

HEADERS += "./src/Logic Model/MediaItem.h"
HEADERS += "./src/Logic Model/Readable.h"
HEADERS += "./src/Logic Model/AudioVisual.h"
HEADERS += "./src/Logic Model/Book.h"
HEADERS += "./src/Logic Model/Film.h"
HEADERS += "./src/Logic Model/Article.h"
HEADERS += "./src/Logic Model/Music.h"
HEADERS += "./src/Logic Model/Podcast.h"
HEADERS += "./src/Save/json/JsonVisitor.h"
HEADERS += "./Test/XmlTests/XmlManagerTest.h"
HEADERS += "./src/Logic Model/Visitor.h"
HEADERS += "./src/Save/xml/XmlVisitor.h"
HEADERS += "./src/Logic Model/ConstVisitor.h"

# Save
HEADERS += "./src/Save/json/JsonManager.h"
HEADERS += "./src/Save/FileManager.h"
HEADERS += "./src/Save/ManagerFactory.h"
HEADERS += "./src/Save/xml/XmlReader.h"
HEADERS += "./src/Save/xml/XmlManager.h"


SOURCES += "./src/Save/xml/XmlManager.cpp"
SOURCES += "./src/Save/json/JsonManager.cpp"
SOURCES += "./src/Save/xml/XmlReader.cpp"
SOURCES += "./src/Save/ManagerFactory.cpp"

#Test
HEADERS += "./Test/JsonTests/JsonTest.h"
HEADERS += "./Test/GUITests/MainWindowTests/LoadFromFileTests.h"

SOURCES += "./Test/JsonTests/JsonTest.cpp"
SOURCES += "./Test/GUITests/MainWindowTests/LoadFromFileTests.cpp"

#GUI
#HEADERS += "./src/GUI/

# TestMain
SOURCES += "./src/main.cpp"
#SOURCES += "./GUITests/MainWindowTests/GuiTest.cpp"
