#pragma once
#include <QWidget>
#include <QVector>
#include <MediaItem.h>
#include <ScrollWidget.h>

class MainDisplay : public QWidget {
    Q_OBJECT
private:
    QMap<QString, QVector<MediaItem*>> mediaItems;
    QScrollArea* mainScroll;
public:
    MainDisplay(QWidget *parent = nullptr);
    void setAreas(QVector<MediaItem*>& items);
    void clearAreas();
private slots:
    void onButtonClicked(MediaItem* item);
public slots:
    void onNoResults(QString query);
signals:
    void itemButtonClicked(MediaItem* item);
};