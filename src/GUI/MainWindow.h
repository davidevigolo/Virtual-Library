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

class MainWindow : public QWidget {
    Q_OBJECT
private:
    FileManager* fileManager;
    QVector<MediaItem*> mediaItems;
    SearchEngine searchEngine;
    void clearView();
    void createHeader();
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
    void search(QString query);
    
    void onButtonClicked(MediaItem* item);
    void onItemDeleted(MediaItem* item);
    void onItemDisplayClosed();
    void onNewItemButtonClicked();
signals:
    void itemsLoaded(QVector<MediaItem*>& items);
};