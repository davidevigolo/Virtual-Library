#include <MainDisplay.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <ScrollPanel.h>
#include <CustomScrollArea.h>
#include <LoadVisitor.h>
#include <iostream>
#include <ScrollWidget.h>

MainDisplay::MainDisplay(QWidget *parent) : QWidget(parent){}

void MainDisplay::setAreas(QVector<MediaItem *> &items)
{
    // Clear the existing layout if it exists
    if (layout() != nullptr) {
        for(auto child : findChildren<ScrollWidget*>()){
            delete child;
            std::cout << "Deleted child" << std::endl;
        }
        delete layout();
    }

    LoadVisitor visitor(mediaItems);
    
    for (MediaItem *item : items)
    {
        item->accept(&visitor);
    }
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    for(auto key : mediaItems.keys()){
        ScrollWidget* scroll = new ScrollWidget(this);
        scroll->setLabel(key);
        scroll->setItems(mediaItems[key]);
        mainLayout->addWidget(scroll);
    }
    setStyleSheet("background-color: black;");
    setLayout(mainLayout);
}