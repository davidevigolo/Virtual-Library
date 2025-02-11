# Virtual-Library.pro

QT += core gui
QT += widgets

CONFIG += c++20

TARGET = Virtual-Library
TEMPLATE = app

TARGET = test1
CONFIG += console c++11
CONFIG += debug
CONFIG -= release

INCLUDEPATH += "./src/Logic Model"
INCLUDEPATH += "./src/Save/xml"
INCLUDEPATH += "./src/Save/json"

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
SOURCES += "./src/Logic Model/JsonVisitor.cpp"
SOURCES += "./src/Logic Model/XmlVisitor.cpp"

HEADERS += "./src/Logic Model/MediaItem.h"
HEADERS += "./src/Logic Model/Readable.h"
HEADERS += "./src/Logic Model/AudioVisual.h"
HEADERS += "./src/Logic Model/Book.h"
HEADERS += "./src/Logic Model/Film.h"
HEADERS += "./src/Logic Model/Article.h"
HEADERS += "./src/Logic Model/Music.h"
HEADERS += "./src/Logic Model/Podcast.h"
HEADERS += "./src/Logic Model/JsonVisitor.h"
HEADERS += "./src/Logic Model/Visitor.h"
HEADERS += "./src/Logic Model/XmlVisitor.h"

# Save
SOURCES += "./src/Save/json/JsonManager.cpp"
HEADERS += "./src/Save/json/JsonManager.h"

HEADERS += "./src/Save/xml/XmlManager.h"
SOURCES += "./src/Save/xml/XmlManager.cpp"
HEADERS += "./src/Save/xml/XmlReader.h"
SOURCES += "./src/Save/xml/XmlReader.cpp"
