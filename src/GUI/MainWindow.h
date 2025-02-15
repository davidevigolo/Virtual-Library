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

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(){
        for (MediaItem* item : mediaItems) {
            delete item;
        }
    }
private:
    FileManager* fileManager;
    QVector<MediaItem*> mediaItems;
    MainDisplay mainDisplay;
    void loadFromFile();
};