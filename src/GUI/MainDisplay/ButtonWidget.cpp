#include <ButtonWidget.h>
#include <qboxlayout.h>
#include <QFontMetrics>

ButtonWidget::ButtonWidget(MediaItem *mediaItem, QWidget *parent) : QWidget(parent), button(this), buttonLabel(this), buttonLayout(this)
{
    // button->setIcon(QIcon("../inception_prova.jpg"));
    button.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button.setStyleSheet("background-color: white;");
    buttonLayout.addWidget(&button, 0, Qt::AlignTop);

    connect(&button, &QPushButton::clicked, this, [this]() {
        button.setStyleSheet("background-color: red;");
    });

    QFontMetrics metrics(buttonLabel.font());
    QString elidedText = metrics.elidedText(QString(mediaItem->getTitle().c_str()), Qt::ElideRight, buttonLabel.width());
    buttonLabel.setText(elidedText);
    buttonLabel.setAlignment(Qt::AlignCenter);
    buttonLabel.setStyleSheet("background-color: white;");
    buttonLabel.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonLayout.addWidget(&buttonLabel, 1, Qt::AlignBottom);
}