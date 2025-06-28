#pragma once
#include <QLabel>
#include <QWidget>
#include <CustomScrollArea.h>
#include <ScrollPanel.h>

/*
    * @class ScrollWidget
    * @brief A custom widget that contains a label and a scrollable panel for displaying media items.
    *
    * The ScrollWidget class provides a container with a label and a scrollable area to display
    * media items. It allows setting the label text and adding items to the scrollable panel.
    * It emits a signal when an item button is clicked.
    *
*/
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