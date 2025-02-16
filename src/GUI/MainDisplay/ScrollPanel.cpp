#include "ScrollPanel.h"
#include "ButtonWidget.h"

ScrollPanel::ScrollPanel(QWidget *parent) : QWidget(parent), layout(this), panelLayout() {
    setStyleSheet("background-color: black;");
    layout.addLayout(&panelLayout);
}

void ScrollPanel::addItem(MediaItem *item) {
    ButtonWidget *button = new ButtonWidget(item,this);
    panelLayout.addWidget(button);
}

void ScrollPanel::setItems(QVector<MediaItem *> &items) {
    for (MediaItem *item : items) {
        addItem(item);
    }
}