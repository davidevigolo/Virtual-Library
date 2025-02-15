#include <QWidget>
#include <QVector>
#include <MediaItem.h>

class MainDisplay : public QWidget {
    Q_OBJECT
private:
    QMap<QString, QVector<MediaItem*>> mediaItems;
public:
    MainDisplay(QWidget *parent = nullptr);
    void setItems(QVector<MediaItem*>& items);
};