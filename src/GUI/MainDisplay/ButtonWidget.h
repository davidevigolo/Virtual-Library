#pragma once
#include <QWidget>
#include <MediaItem.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qboxlayout.h>
#include <qstring.h>

class ButtonWidget : public QWidget
{
    Q_OBJECT
private:
    MediaItem* mediaItem;
    QVBoxLayout buttonLayout;
    QPushButton button;
    QLabel buttonLabel;
public:
    ButtonWidget(MediaItem* mediaItem,QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event) override;
};