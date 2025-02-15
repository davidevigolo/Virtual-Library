#include <ItemWidget.h>
#include <qboxlayout.h>

ItemWidget::ItemWidget(MediaItem *mediaItem, QWidget *parent) : QWidget(parent), button(this), buttonLabel(this), buttonLayout(this)
{
    // button->setIcon(QIcon("../inception_prova.jpg"));
    button.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button.setStyleSheet("background-color: black;");
    buttonLayout.addWidget(&button, 0, Qt::AlignTop);

    connect(&button, &QPushButton::clicked, this, [this]() {
        // emit itemClicked(mediaItem);
    });

    buttonLabel.setAlignment(Qt::AlignCenter);
    buttonLabel.setStyleSheet("background-color: white;");
    buttonLayout.addWidget(&buttonLabel);
}