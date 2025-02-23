#pragma once
#include <QWidget>
#include <MediaItem.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qboxlayout.h>
#include <qstring.h>

/**
 * @class ButtonWidget
 * @brief A custom widget that represents a button with an associated media item.
 * 
 * This class inherits from QWidget and provides a button with a label. When the button is clicked,
 * it emits a signal with the associated media item.
 * 
 * @param mediaItem A pointer to the MediaItem associated with this button.
 * @param parent The parent widget of this ButtonWidget.
 * 
 * @signal itemButtonClicked(MediaItem* mediaItem) Emitted when the button is clicked, passing the associated media item 
 * to make the item display appear.
 */
class ButtonWidget : public QWidget
{
    Q_OBJECT
private:
    MediaItem* mediaItem;
    QVBoxLayout buttonLayout;
    QPushButton button;
    QLabel buttonLabel;
public:
    ButtonWidget(MediaItem* mediaItem,QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void onButtonClicked();
signals:
    void itemButtonClicked(MediaItem* mediaItem);
};