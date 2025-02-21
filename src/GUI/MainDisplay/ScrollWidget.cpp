#include <ScrollWidget.h>

ScrollWidget::ScrollWidget(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    label = new QLabel(this);
    label->setObjectName("scrollLabel");
    layout->addWidget(label);
    scrollPanel = new ScrollPanel(this);
    scrollPanel->setObjectName("scrollPanel");
    scrollPanel->hide();
    connect(scrollPanel, &ScrollPanel::itemButtonClicked, this, &ScrollWidget::onButtonClicked);
    scrollArea = new CustomScrollArea(this);
    scrollArea->setObjectName("scrollArea");
    scrollArea->setWidget(scrollPanel);
    layout->addWidget(scrollArea);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setMinimumHeight(200);
}

void ScrollWidget::setLabel(QString text)
{
    label->setText(text);
}

void ScrollWidget::setItems(QVector<MediaItem *> &items)
{
    scrollPanel->show();
    scrollPanel->setItems(items);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void ScrollWidget::onButtonClicked(MediaItem *item)
{
    emit itemButtonClicked(item);
}
