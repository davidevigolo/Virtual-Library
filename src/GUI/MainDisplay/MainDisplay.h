#pragma once
#include <QWidget>
#include <QVector>
#include <MediaItem.h>
#include <ScrollWidget.h>

/**
 * @class MainDisplay
 * @brief A widget that displays media items within a scrollable area.
 * 
 * The MainDisplay class provides functionality
 * to display and manage media items in multiple scrollable areas, each with its own category. It includes
 * methods to set and clear media items, and handles button click events
 * associated with the media items.
 * 
 * @note This class uses Qt's signal and slot mechanism for event handling.
 *  
 * @section Signals
 * - void itemButtonClicked(MediaItem* item): Emitted when a media item button is clicked.
 * 
 * @section Slots
 * - void onNoResults(QString query): Slot to handle the case when no results are found for a query.
 * - void onButtonClicked(MediaItem* item): Slot to handle button click events for media items.
 * 
 * @section Methods
 * - MainDisplay(QWidget *parent = nullptr): Constructor to initialize the MainDisplay widget.
 * - void setAreas(QVector<MediaItem*>& items): Sets the media items to be displayed.
 * - void clearAreas(): Clears all the media items from the display.
 */
class MainDisplay : public QWidget {
    Q_OBJECT
private:
    QMap<QString, QVector<MediaItem*>> mediaItems;
    QScrollArea* mainScroll;
    QWidget* container;
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