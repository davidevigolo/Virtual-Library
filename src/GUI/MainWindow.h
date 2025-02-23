#pragma once
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QIcon>
#include <QResizeEvent>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <MediaItem.h>
#include "ScrollPanel.h"
#include "CustomScrollArea.h"
#include <FileManager.h>
#include <MainDisplay.h>
#include <SearchEngine.h>

/**
 * @class MainWindow
 * @brief The MainWindow class represents the main window of the GUI application.
 * 
 * This class is responsible for managing the main user interface, including loading and saving files,
 * handling user interactions, and displaying media items. It inherits from QWidget and uses Qt's 
 * signal-slot mechanism to handle events.
 * 
 * @note The destructor ensures that all dynamically allocated MediaItem objects are properly deleted.
 * 
 * @signals
 *   void itemsLoaded(QVector<MediaItem*>& items) - Emitted when media items are loaded for ssort them into a map.
 *   void noResults(QString query) - Emitted when a search query returns no results to show a no result written.
 * 
 */
class MainWindow : public QWidget {
    Q_OBJECT
private:
    FileManager* fileManager;
    QVector<MediaItem*> mediaItems;
    SearchEngine searchEngine;
    void clearView();
    void createHeader();
    void addMainDisplay();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(){
        for (MediaItem* item : mediaItems) {
            delete item;
        }
    }
private slots:
    void loadFromFile();
    void save();
    void saveToFile();
    void onSettingsSignal();
    void search(QString query);
    
    void onButtonClicked(MediaItem* item);
    void onItemDeleted(MediaItem* item);
    void onItemDisplayClosed();
    void onNewItemButtonClicked();
signals:
    void itemsLoaded(QVector<MediaItem*>& items);
    void noResults(QString query);
};