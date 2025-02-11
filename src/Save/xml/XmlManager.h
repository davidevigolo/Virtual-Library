#include <string>
#include <QtCore/qstring.h>
#include "../../Logic Model/MediaItem.h"
class XmlManager
{
private:
    QString filePath;
public:
    XmlManager(QString filePath) : filePath(filePath) {};
    ~XmlManager() = default;

    void save(std::vector<MediaItem*>& media);
    QVector<MediaItem*> load();
};