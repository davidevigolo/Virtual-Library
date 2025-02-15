#include "ScrollPanel.h"
#include "ItemWidget.h"

ScrollPanel::ScrollPanel(QWidget *parent) : QWidget(parent), layout(this), panelLayout(this) {

    layout.addLayout(&panelLayout);
    setLayout(&layout);
    setStyleSheet("background-color: gray;");
}

void ScrollPanel::addItem(MediaItem *item) {
    ItemWidget *itemWidget = new ItemWidget(item,this);
    panelLayout.addWidget(itemWidget);
}