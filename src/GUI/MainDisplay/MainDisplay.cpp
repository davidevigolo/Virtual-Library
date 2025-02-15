#include <MainDisplay.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <ScrollPanel.h>
#include <CustomScrollArea.h>
#include <LoadVisitor.h>

MainDisplay::MainDisplay(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mediaItems = QMap<QString, QVector<MediaItem*>>();
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(35, 35, 35, 35);

    mainLayout->addLayout(layout);
    setLayout(mainLayout);

    setStyleSheet("background-color: gray;");
}

void MainDisplay::setItems(QVector<MediaItem *> &items)
{
    LoadVisitor visitor(mediaItems);
    for (MediaItem *item : items)
    {
        item->accept(&visitor);
    }
    for(auto key : mediaItems.keys()){
        CustomScrollArea *scrollArea = new CustomScrollArea(this);
        ScrollPanel *scrollPanel = new ScrollPanel(this);
        scrollArea->setWidget(scrollPanel);
        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        layout()->addWidget(scrollArea);
        for(MediaItem* item : mediaItems[key]){
            scrollPanel->addItem(item);
        }
    }
}