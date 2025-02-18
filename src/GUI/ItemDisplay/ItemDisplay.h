#pragma once
#include <MediaItem.h>
#include <QWidget>

class ItemDisplay : public QWidget
{
    Q_OBJECT
private:
    MediaItem* item;
public:
    ItemDisplay(MediaItem* item = nullptr, QWidget* parent = nullptr);
private slots:
    void onEdit();
    void onDeletion();
    void onGoBack();
signals:
    void itemChanged(MediaItem* item);
    void itemDeleted(MediaItem* item);
    void itemDisplayClosed();
};
