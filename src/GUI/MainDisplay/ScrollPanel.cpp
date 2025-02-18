#include "ScrollPanel.h"
#include "ButtonWidget.h"
#include <iostream>

ScrollPanel::ScrollPanel(QWidget *parent) : QWidget(parent), layout(this), panelLayout() {
    setStyleSheet("background-color: black;");
    layout.addLayout(&panelLayout);
}

void ScrollPanel::addItem(MediaItem *item) {
    ButtonWidget *button = new ButtonWidget(item,this);
    connect(button, &ButtonWidget::itemButtonClicked, this, &ScrollPanel::onButtonClicked);
    panelLayout.addWidget(button);
}

void ScrollPanel::setItems(QVector<MediaItem *> &items) {
    // Clear existing items
    for (ButtonWidget *button : findChildren<ButtonWidget*>()) {
        panelLayout.removeWidget(button);
        delete button;
    }

    for (MediaItem *item : items) {
        addItem(item);
    }
}

void ScrollPanel::onButtonClicked(MediaItem *item) {
    emit itemButtonClicked(item);
}   