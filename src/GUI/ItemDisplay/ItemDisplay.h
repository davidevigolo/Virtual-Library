#pragma once
#include <MediaItem.h>
#include <QWidget>
#include <QPushButton>
#include <ImageButton.h>

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
    QString imagePath;
public:
    ItemDisplay(MediaItem* item = nullptr, QWidget* parent = nullptr);
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
