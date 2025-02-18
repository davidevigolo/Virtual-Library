#include <MainDisplay.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <ScrollPanel.h>
#include <CustomScrollArea.h>
#include <LoadVisitor.h>
#include <iostream>
#include <ScrollWidget.h>

MainDisplay::MainDisplay(QWidget *parent) : QWidget(parent) , 
    scroll(
        {
        new ScrollWidget(this),
        new ScrollWidget(this),
        new ScrollWidget(this),
        new ScrollWidget(this),
        new ScrollWidget(this)
        }
    )
{
    connect(scroll[0], &ScrollWidget::itemButtonClicked, this, &MainDisplay::onButtonClicked);
    connect(scroll[1], &ScrollWidget::itemButtonClicked, this, &MainDisplay::onButtonClicked);
    connect(scroll[2], &ScrollWidget::itemButtonClicked, this, &MainDisplay::onButtonClicked);
    connect(scroll[3], &ScrollWidget::itemButtonClicked, this, &MainDisplay::onButtonClicked);
    connect(scroll[4], &ScrollWidget::itemButtonClicked, this, &MainDisplay::onButtonClicked);
}

void MainDisplay::setAreas(QVector<MediaItem *> &items)
{
    LoadVisitor visitor(mediaItems);
    for(auto key : mediaItems.keys()){
        mediaItems[key].clear();
    }
    
    for (MediaItem *item : items)
    {
        item->accept(&visitor);
    }
    delete layout();
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    int i = 0;
    for(auto key : mediaItems.keys()){
        scroll[i]->setLabel(key);
        scroll[i]->setItems(mediaItems[key]);
        mainLayout->addWidget(scroll[i]);
        i++;
    }
    setStyleSheet("background-color: black;");
    setLayout(mainLayout);
}

void MainDisplay::onButtonClicked(MediaItem *item)
{
    emit itemButtonClicked(item);
}