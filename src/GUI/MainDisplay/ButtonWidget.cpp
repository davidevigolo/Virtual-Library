#include <ButtonWidget.h>
#include <qboxlayout.h>
#include <QFontMetrics>
#include <QResizeEvent>
#include <MainWindow.h>
#include <QFile>

ButtonWidget::ButtonWidget(MediaItem *mediaItem, QWidget *parent) : QWidget(parent), button(this), buttonLabel(this), buttonLayout(this), mediaItem(mediaItem)
{
    // Set initial button size ratio to 4:3
    int buttonWidth = 200; // Example width
    int buttonHeight = buttonWidth * 3 / 4;
    button.setFixedSize(buttonWidth, buttonHeight);

    button.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button.setStyleSheet("background-color: white; color: black;");

    QFile image(mediaItem->getImage().c_str());
    if (!image.exists()) {
        qWarning() << "Image file does not exist:" << mediaItem->getImage().c_str();
        QPixmap pixmap(":/images/resources/no_image.jpeg");
        button.setIcon(pixmap); // Set a default or empty icon
    } else {
        button.setIcon(QIcon(image.fileName()));
    }

    buttonLayout.addWidget(&button, 0, Qt::AlignTop);

    connect(&button, &QPushButton::clicked, this, &ButtonWidget::onButtonClicked);

    QFontMetrics metrics(buttonLabel.font());
    QString elidedText = metrics.elidedText(QString(mediaItem->getTitle().c_str()), Qt::ElideRight, button.width());
    buttonLabel.setText(elidedText);
    buttonLabel.setAlignment(Qt::AlignCenter);
    buttonLabel.setStyleSheet("background-color: white; color: black;");
    buttonLabel.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    buttonLabel.setFixedSize(button.width(), buttonLabel.sizeHint().height());
    buttonLayout.addWidget(&buttonLabel, 0, Qt::AlignBottom);

    setLayout(&buttonLayout);
}

void ButtonWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    int buttonHeight = event->size().height();
    int buttonWidth = buttonHeight * 16 / 9 ;
    button.setFixedSize(buttonWidth, buttonHeight);

    QFontMetrics metrics(buttonLabel.font());
    QString elidedText = metrics.elidedText(QString(mediaItem->getTitle().c_str()), Qt::ElideRight, button.width());
    buttonLabel.setText(elidedText);
    buttonLabel.setFixedSize(button.width(), buttonLabel.sizeHint().height());
    button.setIconSize(QSize(button.width(), button.height()));
}

void ButtonWidget::onButtonClicked()
{
    emit itemButtonClicked(mediaItem);
}