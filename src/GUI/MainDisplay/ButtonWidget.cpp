#include <ButtonWidget.h>
#include <qboxlayout.h>
#include <QFontMetrics>
#include <QResizeEvent>
#include <MainWindow.h>
#include <QFile>

ButtonWidget::ButtonWidget(MediaItem *mediaItem, QWidget *parent) : QWidget(parent), mediaItem(mediaItem), buttonLayout(this), button(this), buttonLabel(this)
{
    // Set initial button size ratio to 5:3
    int buttonWidth = 200;
    int buttonHeight = buttonWidth * 3 / 5;
    button.setFixedSize(buttonWidth, buttonHeight);

    button.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button.setStyleSheet("background-color: white; color: black;");

    QPixmap pixmap(":/images/resources/no_image.jpeg");
    QFile image(mediaItem->getImage().c_str());
    if (!image.exists())
    {
        qWarning() << "Image file does not exist:" << mediaItem->getImage().c_str();
        button.setIcon(pixmap); // Set default or empty icon
    }
    else
    {
        pixmap = QPixmap(image.fileName());
        if (pixmap.isNull())
        {
            qWarning() << "Failed to load image:" << image.fileName();
            button.setIcon(pixmap); // Set a default image if the loading fails
        }
        else
        {
            button.setIcon(pixmap);
        }
    }

    // Adjust icon size to fit button while maintaining aspect ratio
    QSize iconSize = pixmap.size();
    iconSize.scale(button.width(),button.width(), Qt::AspectRatioMode::KeepAspectRatio);
    button.setIconSize(iconSize);
    button.setStyleSheet("border: none; padding: 0px; margin: 0px;");


    buttonLayout.addWidget(&button, 0, Qt::AlignTop);

    connect(&button, &QPushButton::clicked, this, &ButtonWidget::onButtonClicked);

    QFontMetrics metrics(buttonLabel.font());
    QString elidedText = metrics.elidedText(QString(mediaItem->getTitle().c_str()), Qt::ElideRight, button.width());
    buttonLabel.setObjectName("itemButtonLabel");
    buttonLabel.setText(elidedText);
    buttonLabel.setAlignment(Qt::AlignCenter);
    buttonLabel.setStyleSheet("background-color: white; color: black;");
    buttonLabel.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    buttonLabel.setFixedSize(button.width(), buttonLabel.sizeHint().height());
    buttonLabel.setStyleSheet("border: none; padding: 0px; margin: 0px;");
    buttonLabel.setStyleSheet("background-color: " + palette().window().color().name() + ";");
    buttonLayout.addWidget(&buttonLabel, 0, Qt::AlignBottom);

    setLayout(&buttonLayout);
}

void ButtonWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    int buttonHeight = event->size().height();
    int buttonWidth = buttonHeight * 16 / 9;
    button.setFixedSize(buttonWidth, buttonHeight);

    QFontMetrics metrics(buttonLabel.font());
    QString elidedText = metrics.elidedText(QString(mediaItem->getTitle().c_str()), Qt::ElideRight, button.width());
    buttonLabel.setText(elidedText);
    buttonLabel.setFixedSize(button.width(), buttonLabel.sizeHint().height());
}

void ButtonWidget::onButtonClicked()
{
    emit itemButtonClicked(mediaItem);
}