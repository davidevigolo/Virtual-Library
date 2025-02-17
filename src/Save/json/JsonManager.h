#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QVector>
#include <Article.h>
#include <Book.h>
#include <Film.h>
#include <Music.h>
#include <Podcast.h>
#include <FileManager.h>

class JsonManager : public FileManager{
    private:
        QString filePath;
    public:
        JsonManager(const QString& filePath) : filePath(filePath) {}
        ~JsonManager();
        std::vector<std::string> JsonArrToVec(const QJsonArray &array) const;
        MediaItem* ObjectLoader(const QString& className, const QJsonObject& obj) const;
        QVector<MediaItem*> load() const;
        void save(QVector<MediaItem*>& item) const;
        void setPath(const QString& path);
        QString getPath() const;
        
};

#endif // JSONMANAGER_H