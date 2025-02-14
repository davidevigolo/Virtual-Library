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

#GUI 
HEADERS += "./src/GUI/MainWindow.h"
HEADERS += "./src/GUI/ScrollPanel.h"
HEADERS += "./src/GUI/CustomScrollArea.h"
HEADERS += "./src/GUI/LoadVisitor.h"

SOURCES += "./src/GUI/MainWindow.cpp"
SOURCES += "./src/GUI/ScrollPanel.cpp"
SOURCES += "./src/GUI/CustomScrollArea.cpp"
SOURCES += "./src/GUI/LoadVisitor.cpp"

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
SOURCES += "./src/Save/json/JsonManager.cpp"
HEADERS += "./src/Save/json/JsonManager.h"

HEADERS += "./src/Save/xml/XmlManager.h"
SOURCES += "./src/Save/xml/XmlManager.cpp"
HEADERS += "./src/Save/xml/XmlReader.h"
SOURCES += "./src/Save/xml/XmlReader.cpp"

#Test
HEADERS += "./Test/jsonTests/JsonTest.h"
#HEADERS += "./Test/GUITests/MainWindowTests/LoadFromFileTests.h"

SOURCES += "./Test/jsonTests/JsonTest.cpp"
#SOURCES += "./Test/GUITests/MainWindowTests/LoadFromFileTests.cpp"

# TestMain
SOURCES += "./Test/TestMain.cpp"
