#pragma once
#include <QLabel>
#include <QWidget>
#include <CustomScrollArea.h>
#include <ScrollPanel.h>


class ScrollWidget : public QWidget{
    Q_OBJECT
private:
    QLabel* label;
    ScrollPanel* scrollPanel;
    CustomScrollArea* scrollArea;
    QVBoxLayout* layout;
public:
    ScrollWidget(QWidget *parent = nullptr);
    void setLabel(QString text);
    void setItems(QVector<MediaItem*> &items);
private slots:
    void onButtonClicked(MediaItem* item);
signals:
    void itemButtonClicked(MediaItem* mediaItem);
};