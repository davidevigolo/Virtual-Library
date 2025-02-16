#include <MainDisplay.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <ScrollPanel.h>
#include <CustomScrollArea.h>
#include <LoadVisitor.h>
#include <iostream>

MainDisplay::MainDisplay(QWidget *parent) : QWidget(parent){}

void MainDisplay::setAreas(QVector<MediaItem *> &items)
{
    LoadVisitor visitor(mediaItems);
    
    for (MediaItem *item : items)
    {
        item->accept(&visitor);
    }
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    for(auto key : mediaItems.keys()){
        CustomScrollArea *scrollArea = new CustomScrollArea(this);
        ScrollPanel *scrollPanel = new ScrollPanel();
        scrollPanel->setItems(mediaItems[key]);
        scrollArea->setWidget(scrollPanel);
        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setStyleSheet("background-color: gray;");
        QLabel *label = new QLabel(key);
        label->setStyleSheet("font-size: 20px; color: white;");
        mainLayout->addWidget(label);
        mainLayout->addWidget(scrollArea);
    }
    setStyleSheet("background-color: black;");
    setLayout(mainLayout);
}