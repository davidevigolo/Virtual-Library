#include <MainDisplay.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <ScrollPanel.h>
#include <CustomScrollArea.h>
#include <LoadVisitor.h>
#include <iostream>
#include <ScrollWidget.h>

MainDisplay::MainDisplay(QWidget *parent) : QWidget(parent), mainScroll(new QScrollArea(this))
{
    setLayout(new QVBoxLayout(this));
    layout()->addWidget(mainScroll);

    mainScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    mainScroll->setWidgetResizable(true);
    mainScroll->hide();
}

void MainDisplay::setAreas(QVector<MediaItem *> &items)
{
    mainScroll->show();
    LoadVisitor visitor(mediaItems);
    int i = 0;
    for(auto key : mediaItems.keys()){
        mediaItems[key].clear();
    }
    // auto scrolls = findChildren<ScrollWidget*>();
    // for(auto scroll : scrolls){
        
    //     delete scroll;
    // }

    for (MediaItem *item : items)
    {
        item->accept(&visitor);
    }
    
    QVBoxLayout *mainLayout = new QVBoxLayout();
    
    for(auto key : mediaItems.keys()){
        scroll.append(new ScrollWidget(mainScroll));
        connect(scroll[i], &ScrollWidget::itemButtonClicked, this, &MainDisplay::onButtonClicked);
        scroll[i]->setLabel(key);
        scroll[i]->setItems(mediaItems[key]);
        mainLayout->addWidget(scroll[i++]);
    }
    QWidget *container = new QWidget();
    container->setLayout(mainLayout);
    mainScroll->setWidget(container);
}

void MainDisplay::onButtonClicked(MediaItem *item)
{
    emit itemButtonClicked(item);
}