#pragma once
#include <QWidget>
#include <QVector>
#include <MediaItem.h>
#include <ScrollWidget.h>

class MainDisplay : public QWidget {
    Q_OBJECT
private:
    QMap<QString, QVector<MediaItem*>> mediaItems;
    QVector<ScrollWidget*> scroll;
public:
    MainDisplay(QWidget *parent = nullptr);
    void setAreas(QVector<MediaItem*>& items);
};