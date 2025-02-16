#include <QWidget>
#include <MediaItem.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qboxlayout.h>

class ItemWidget : public QWidget
{
    Q_OBJECT
private:
    MediaItem* mediaItem;
    QPushButton button;
    QLabel buttonLabel;
    QVBoxLayout buttonLayout;
public:
    ItemWidget(MediaItem* mediaItem,QWidget *parent = nullptr);
};