#include <QWidget>
#include <MediaItem.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qboxlayout.h>
#include <qstring.h>

class ButtonWidget : public QWidget
{
    Q_OBJECT
private:
    MediaItem* mediaItem;
    QPushButton button;
    QLabel buttonLabel;
    QVBoxLayout buttonLayout;
public:
    ButtonWidget(MediaItem* mediaItem,QWidget *parent = nullptr);
};