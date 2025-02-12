#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QVector>
#include "../../Logic Model/Article.h"
#include "../../Logic Model/Book.h"
#include "../../Logic Model/Film.h"
#include "../../Logic Model/Music.h"
#include "../../Logic Model/Podcast.h"

class JsonManager : public QObject {
    private:
        QString filePath;
    public:
        JsonManager(const QString& filePath) : filePath(filePath) {}
        ~JsonManager();
        std::vector<std::string> JsonArrToVec(const QJsonArray &array) const;
        MediaItem* ObjectLoader(const QString& className, const QJsonObject& obj) const;
        QVector<MediaItem*> readJson() const;
        void save(QVector<MediaItem*> item) const;
        
};

#endif // JSONMANAGER_H