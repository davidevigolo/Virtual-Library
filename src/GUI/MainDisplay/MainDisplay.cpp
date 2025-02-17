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
    CustomScrollArea *mainScrollArea = new CustomScrollArea(this);
    QWidget *mainScrollPanel = new QWidget(this);
    QVBoxLayout *mainScrollPanelLayout = new QVBoxLayout(mainScrollPanel);

    for (int i = 0; i < 5; ++i) {
        CustomScrollArea *scrollArea = new CustomScrollArea(this);
        ScrollPanel *scrollPanel = new ScrollPanel(this);
        // Assuming mediaItems[key] is a valid list of items for each scroll panel
        scrollPanel->setItems(mediaItems[mediaItems.keys().at(i % mediaItems.keys().size())]);
        scrollPanel->setMinimumSize(200, 200);
        scrollArea->setWidget(scrollPanel);
        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setStyleSheet("background-color: gray;");

        QLabel *label = new QLabel(mediaItems.keys().at(i % mediaItems.keys().size()));
        label->setStyleSheet("font-size: 20px; color: white;");

        QVBoxLayout *containerLayout = new QVBoxLayout();
        containerLayout->addWidget(label);
        containerLayout->addWidget(scrollArea);

        QWidget *container = new QWidget();
        container->setLayout(containerLayout);

        mainScrollPanelLayout->addWidget(container);
    }

    mainScrollPanel->setLayout(mainScrollPanelLayout);
    mainScrollArea->setWidget(mainScrollPanel);
    mainScrollArea->setWidgetResizable(true);
    mainScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    mainScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mainLayout->addWidget(mainScrollArea);
    setStyleSheet("background-color: black;");
    setLayout(mainLayout);
}