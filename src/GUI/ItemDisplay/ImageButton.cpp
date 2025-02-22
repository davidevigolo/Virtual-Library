#include <ImageButton.h>
#include <qboxlayout.h>
#include <QFontMetrics>
#include <QResizeEvent>
#include <MainWindow.h>
#include <QFile>
#include <QDebug>

ImageButton::ImageButton(QWidget *parent, QString imagePath) : QWidget(parent), button(this), imagePath(imagePath)
{
    button.setFixedSize(QSize(1000,1000));

    button.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button.setStyleSheet("background-color: " + palette().window().color().name() + "; color: black; margin: 0px; padding: 0px; border: none;");
    button.setFocusPolicy(Qt::NoFocus);
    button.setEnabled(true);

    connect(&button, &QPushButton::clicked, this, &ImageButton::onImageButtonClicked);
}
void ImageButton::setIcon(const QString &iconPath)
{
    imagePath = iconPath;
    button.setIcon(QIcon(iconPath));
}
void ImageButton::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if(event->size().width() > event->size().height())
        button.setFixedSize(event->size().height(), event->size().height());
    else
        button.setFixedSize(event->size().width(), event->size().width());

    // Set the icon size to the size of the button
    button.setIconSize(button.size());
}

void ImageButton::setEnabled(bool _enabled)
{
    
    enabled = _enabled;
}

void ImageButton::onImageButtonClicked()
{
    qDebug() << "ImageButton clicked";
    if(!enabled)
        return;
    emit imageButtonClicked();
}