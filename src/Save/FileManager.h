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
};