#pragma once
#include <qstring.h>
#include <qbytearray.h>
#include <MediaItem.h>

/*
    * @class FileManager
    * @brief Common interface class for managing file operations related to media items.
    *
    * This class defines the interface for saving and loading media items from a file.
    * It provides methods to set the file path and retrieve it.
*/
class FileManager {
public:
    FileManager() {};
    virtual ~FileManager() {};
    virtual void save(QVector<MediaItem*>& media) const = 0;
    virtual QVector<MediaItem*> load() const = 0;
    virtual void setPath(const QString& path) = 0;
    virtual QString getPath() const = 0;
};