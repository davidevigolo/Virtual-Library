#pragma once
#include <QWidget>
#include <MediaItem.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qboxlayout.h>
#include <qstring.h>

/*
    This class is a custom widget that is used to display a
    clickable image button. It is used in the ItemDisplay class
    to modify the image of the media item.   
*/
class ImageButton : public QWidget
{
    Q_OBJECT
private:
    QPushButton button;
    bool enabled;
    QString imagePath;
public:
    ImageButton(QWidget *parent = nullptr, QString imagePath = "");
    void resizeEvent(QResizeEvent *event) override;
    void setIcon(const QString &iconPath);
    void setEnabled(bool enabled);
private slots:
    void onImageButtonClicked();
signals:
    void imageButtonClicked();
};