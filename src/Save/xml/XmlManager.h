#pragma once
#include <string>
#include <QtCore/qstring.h>
#include "../../Logic Model/MediaItem.h"
#include <FileManager.h>
class XmlManager : public FileManager
{
private:
    QString filePath;
public:
    XmlManager(QString filePath) : filePath(filePath) {};
    ~XmlManager() = default;

    void save(QVector<MediaItem*>& media) const override;
    QVector<MediaItem*> load() const override;
};