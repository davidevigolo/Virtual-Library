#include <ScrollWidget.h>

ScrollWidget::ScrollWidget(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    label = new QLabel(this);
    layout->addWidget(label);
    scrollPanel = new ScrollPanel(this);
    scrollArea = new CustomScrollArea(this);
    layout->addWidget(scrollArea);
}

void ScrollWidget::setLabel(QString text)
{
    label->setText(text);
    label->setStyleSheet("color: white;");
}

void ScrollWidget::setItems(QVector<MediaItem *> &items)
{
    scrollPanel->setItems(items);
    scrollArea->setWidget(scrollPanel);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet("background-color: gray;");
}
