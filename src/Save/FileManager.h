#pragma once
#include <qstring.h>
#include <qbytearray.h>
#include <MediaItem.h>

class FileManager {
public:
    FileManager() {};
    virtual ~FileManager() {};
    virtual void save(QVector<MediaItem*>& media) const = 0;
    virtual QVector<MediaItem*> load() const = 0;
    virtual void setPath(const QString& path) = 0;
    virtual QString getPath() const = 0;
};