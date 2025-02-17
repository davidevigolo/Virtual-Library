#include <QWidget>
#include <QVector>
#include <MediaItem.h>

class MainDisplay : public QWidget {
    Q_OBJECT
private:
    QMap<QString, QVector<MediaItem*>> mediaItems;
public:
    MainDisplay(QWidget *parent = nullptr);
public slots:
    void setAreas(QVector<MediaItem*>& items);
};