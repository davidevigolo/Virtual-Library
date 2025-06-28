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


/**
 * @class ScrollPanel
 * @brief A custom QWidget that contains a horizontal layout for displaying media items.
 *
 * The ScrollPanel class provides a container with a horizontal layout to display
 * media items. It allows adding individual items or setting a collection of items.
 * It also provides a signal for item button clicks.
 
 * @signal itemButtonClicked
 * @brief Emitted when a media item's button is clicked.
 * @param mediaItem The media item associated with the clicked button.
 */
class ScrollPanel : public QWidget {
    Q_OBJECT
private:
    QHBoxLayout* panelLayout;
public:
    ScrollPanel(QWidget *parent = nullptr);
    void addItem(MediaItem* item);
    void setItems(QVector<MediaItem*>& items);
private slots:
    void onButtonClicked(MediaItem* item);
signals:
    void itemButtonClicked(MediaItem* mediaItem);
};