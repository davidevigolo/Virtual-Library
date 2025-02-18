#include "CustomScrollArea.h"

CustomScrollArea::CustomScrollArea(QWidget *parent) : QScrollArea(parent) {};

void CustomScrollArea::resizeEvent(QResizeEvent *event){
    QScrollArea::resizeEvent(event);
    QWidget *widget = this->widget();
    if (widget) {
        QSize size = event->size();
        widget->setFixedHeight(size.height());
        for (auto button : widget->findChildren<ButtonWidget*>()) {
            button->resize(button->size());
        }
    }
}