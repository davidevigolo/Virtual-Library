#pragma once
#include <MediaItem.h>
#include <QWidget>
#include <QPushButton>
#include <ImageButton.h>

/**
 * @class ItemDisplay
 * @brief A widget for displaying and editing media items.
 * 
 * The ItemDisplay class provides a user interface for displaying and editing
 * media items. It includes buttons for editing, deleting, saving, and canceling
 * changes to the media item, as well as a button for selecting an image.
 * 
 * @inherits QWidget
 * 
 * @param item A pointer to the MediaItem to be displayed and edited.
 * @param parent The parent widget.
 * @param newItem A flag indicating whether the item is a new item.
 * 
 * @signal itemChanged(MediaItem* item) Emitted when the media item is changed.
 * @signal itemDeleted(MediaItem* item) Emitted when the media item is deleted.
 * @signal itemDisplayClosed() Emitted when the item display is closed.
 * 
 * @slot void onEdit() Slot for handling the edit button click event.
 * @slot void onDeletion() Slot for handling the delete button click event.
 * @slot void onGoBack() Slot for handling the go back button click event.
 * @slot void onSave() Slot for handling the save button click event.
 * @slot void onCancel() Slot for handling the cancel button click event.
 * @slot void onImageButtonClicked() Slot for handling the image button click event.
 */
class ItemDisplay : public QWidget
{
    Q_OBJECT
private:
    MediaItem* item;

    QPushButton* editButton;
    QPushButton* deleteButton;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    ImageButton* imageButton;
    bool newItem;
    QString imagePath;
    QWidget* fieldContainer;
public:
    ItemDisplay(MediaItem* item = nullptr, QWidget* parent = nullptr, bool newItem = false);
private:
    void setFieldsReadOnly(bool value);
private slots:
    void onEdit();
    void onDeletion();
    void onGoBack();
    void onSave();
    void onCancel();
    void onImageButtonClicked();
signals:
    void itemChanged(MediaItem* item);
    void itemDeleted(MediaItem* item);
    void itemDisplayClosed();
};
