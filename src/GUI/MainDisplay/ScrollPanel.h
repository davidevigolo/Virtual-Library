#pragma once
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QIcon>
#include <QResizeEvent>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <MediaItem.h>


class ScrollPanel : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout layout;
    QHBoxLayout panelLayout;
public:
    ScrollPanel(QWidget *parent = nullptr);
    void addItem(MediaItem* item);
    void setItems(QVector<MediaItem*>& items);
private slots:
    void onButtonClicked(MediaItem* item);
signals:
    void itemButtonClicked(MediaItem* mediaItem);
};