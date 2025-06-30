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

    QLabel *noResult = new QLabel("No results found",this);
    noResult->setObjectName("noResultLabel");
    noResult->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    layout()->addWidget(noResult);
    noResult->hide();

    mainScroll->setWidgetResizable(true);
    mainScroll->hide();//to ensure that the scroll is hidden until the items are set
}

void MainDisplay::setAreas(QVector<MediaItem *> &items)
{
    LoadVisitor visitor(mediaItems);

    clearAreas();

    for (MediaItem *item : items)
    {
        item->accept(&visitor);
    }

    mainScroll->show();
    findChild<QLabel *>("noResultLabel")->hide();
    
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QWidget *container = new QWidget();
    container->setObjectName("container");
    container->setLayout(mainLayout);

    for (auto key : mediaItems.keys())//set the orizontal scroll areas
    {
        ScrollWidget *scroll = new ScrollWidget(container);
        connect(scroll, &ScrollWidget::itemButtonClicked, this, &MainDisplay::onButtonClicked);
        scroll->setLabel(key);
        scroll->setItems(mediaItems[key]);
        mainLayout->addWidget(scroll);
    }

    mainScroll->setWidget(container);
}

void MainDisplay::clearAreas()
{
    for (auto key : mediaItems.keys())
    {
        mediaItems[key].clear();
        mediaItems.remove(key);
    }

    auto scrolls = findChildren<ScrollWidget *>();
    QWidget *_container = findChild<QWidget *>("container");
    for (auto scroll : scrolls)
    {
        _container->layout()->removeWidget(scroll);
        scroll->deleteLater();
    }
}

void MainDisplay::onButtonClicked(MediaItem *item)
{
    emit itemButtonClicked(item);
}

void MainDisplay::onNoResults(QString query)
{
    mainScroll->hide();
    QLabel* noResultLabel = findChild<QLabel *>("noResultLabel");
    noResultLabel->setText("No results found for: " + query);
    noResultLabel->show();
}