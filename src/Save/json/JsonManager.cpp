#include "JsonManager.h"

JsonManager::~JsonManager() {}

std::vector<std::string> JsonManager::JsonArrToVec(const QJsonArray &array) const { //Convert a QJsonArray to a std::vector<std::string>
    std::vector<std::string> vec;
    for (const QJsonValue &value : array) {
        vec.push_back(value.toString().toStdString());  // Converte il valore in std::string
    }
    return vec;
}

MediaItem* JsonManager::ObjectLoader(const QString& className, const QJsonObject& obj) const { //create a media item from a json object
        MediaItem* media = new MediaItem(
        obj["Title"].toString().toStdString(), 
        obj["Author"].toString().toStdString(), 
        obj["ReleaseDate"].toString().toStdString(), 
        obj["ProductionHouse"].toString().toStdString(), 
        obj["Genre"].toString().toStdString(), 
        JsonArrToVec(obj["Tags"].toArray()), 
        obj["Format"].toString().toStdString(), 
        obj["Language"].toString().toStdString(), 
        obj["Used"].toString().toStdString(),
        obj["Image"].toString().toStdString()
        );
    if (className == "Article" || className == "Book") {
        media = new Readable(
            media,
            obj["Edition"].toString().toStdString(), 
            obj["Pages"].toInt()
        );
        if(className == "Article") {
            media = new Article(
                static_cast<Readable*>(media),
                obj["Publisher"].toString().toStdString()
            );
        }else{
            media = new Book(
                static_cast<Readable*>(media),
                obj["ISBN"].toInt()
            );
        } 
     }else{
        media = new AudioVisual(
            media,
            obj["Duration"].toString().toUInt()
        );
        if(className == "Film"){
            media = new Film(
                static_cast<AudioVisual*>(media),
                obj["Tecnic"].toString().toStdString(), 
                obj["Framerate"].toDouble(), 
                obj["Director"].toString().toStdString()
            );
        } else if (className == "Music") {
            media = new Music(
                static_cast<AudioVisual*>(media),
                obj["Album"].toString().toStdString()
            );
        } else if (className == "Podcast") {
            media = new Podcast(
                static_cast<AudioVisual*>(media),
                obj["Episodes"].toInt()
            );
        } else {
            qWarning() << "Unrecognised class" << className;
        }
    }
    return media;
}

QVector<MediaItem*> JsonManager::readJson() const {
    QVector<MediaItem*> Library; //create the vector of readen objects
    QFile file(filePath); //load the file

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open file:" << filePath;
        return Library;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError; //to check parsin errors
    QJsonDocument document = QJsonDocument::fromJson(data, &parseError); //to parse the data and save parsing errors

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << parseError.errorString();
        return Library;
    }

    QJsonArray jsonArray = document.array();
    for (const QJsonValue& value : jsonArray) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject(); //save the object information
            QString className = obj["Class"].toString(); //save the class information
            Library.push_back(ObjectLoader(className, obj)); //add the readen object to the vector (once created)
        }
    }

    return Library;
}

void JsonManager::save(QVector<MediaItem*> Library) const{
    QFile file(filePath);

    JsonVisitor* visitor = new JsonVisitor();
    QJsonArray jsonArray;

    for(auto media : Library){
        media->accept(visitor);
        jsonArray.push_back(visitor->getObject());
    }

    QJsonDocument newDocument(jsonArray);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open file:" << filePath;
        return;
    }
    file.write(newDocument.toJson());
    file.close();
    delete visitor;
}
