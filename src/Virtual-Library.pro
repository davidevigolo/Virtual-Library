# Virtual-Library.pro

QT += core gui
QT += widgets

CONFIG += c++20

TARGET = Virtual-Library
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

# Add additional directories for headers and sources if needed
# INCLUDEPATH += path/to/headers
# DEPENDPATH += path/to/sources

# Add any additional libraries if needed
# LIBS += -L/path/to/lib -lname