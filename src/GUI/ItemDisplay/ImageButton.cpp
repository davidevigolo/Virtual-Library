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
    button.setStyleSheet("background-color: #1e2124; color: black;");
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
    button.setIconSize(QSize(button.width(), button.height()));
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