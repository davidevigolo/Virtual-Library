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
    MediaItem* media = nullptr;
    if (className == "Article"){
        media = new Article(
            obj["Title"].toString().toStdString(), 
            obj["Author"].toString().toStdString(), 
            obj["ReleaseDate"].toString().toStdString(), 
            obj["ProductionHouse"].toString().toStdString(), 
            obj["Genre"].toString().toStdString(), 
            JsonArrToVec(obj["Tags"].toArray()),
            obj["Format"].toString().toStdString(), 
            obj["Language"].toString().toStdString(), 
            obj["Used"].toString().toStdString(), 
            obj["Edition"].toString().toStdString(), 
            obj["Pages"].toInt(), 
            obj["Publisher"].toString().toStdString()
        );
    } else if (className == "Book") {
        media = new Book(
            obj["Title"].toString().toStdString(), 
            obj["Author"].toString().toStdString(), 
            obj["ReleaseDate"].toString().toStdString(), 
            obj["ProductionHouse"].toString().toStdString(), 
            obj["Genre"].toString().toStdString(), 
            JsonArrToVec(obj["Tags"].toArray()),
            obj["Format"].toString().toStdString(), 
            obj["Language"].toString().toStdString(), 
            obj["Used"].toString().toStdString(), 
            obj["Edition"].toString().toStdString(), 
            obj["Pages"].toInt(), 
            obj["ISBN"].toInt()
        );
    } else if (className == "Film") {
        media = new Film(
            obj["Title"].toString().toStdString(), 
            obj["Author"].toString().toStdString(), 
            obj["ReleaseDate"].toString().toStdString(), 
            obj["ProductionHouse"].toString().toStdString(), 
            obj["Genre"].toString().toStdString(), 
            JsonArrToVec(obj["Tags"].toArray()), 
            obj["Format"].toString().toStdString(), 
            obj["Language"].toString().toStdString(), 
            obj["Used"].toString().toStdString(), 
            obj["Duration"].toString().toStdString(), 
            obj["Tecnica"].toString().toStdString(), 
            obj["Framerate"].toDouble(), 
            obj["Director"].toString().toStdString()
        );
    } else if (className == "Music") {
        media = new Music(
            obj["Title"].toString().toStdString(), 
            obj["Author"].toString().toStdString(), 
            obj["ReleaseDate"].toString().toStdString(), 
            obj["ProductionHouse"].toString().toStdString(), 
            obj["Genre"].toString().toStdString(), 
            JsonArrToVec(obj["Tags"].toArray()), 
            obj["Format"].toString().toStdString(), 
            obj["Language"].toString().toStdString(), 
            obj["Used"].toString().toStdString(), 
            obj["Duration"].toString().toStdString(), 
            obj["Album"].toString().toStdString()
        );
    } else if (className == "Podcast") {
        media = new Podcast(
            obj["Title"].toString().toStdString(), 
            obj["Author"].toString().toStdString(), 
            obj["ReleaseDate"].toString().toStdString(), 
            obj["ProductionHouse"].toString().toStdString(), 
            obj["Genre"].toString().toStdString(), 
            JsonArrToVec(obj["Tags"].toArray()),
            obj["Format"].toString().toStdString(), 
            obj["Language"].toString().toStdString(), 
            obj["Used"].toString().toStdString(), 
            obj["Duration"].toString().toStdString(), 
            obj["Episodes"].toInt()
        );
    }else {
        qWarning() << "Unrecognised class" << className;
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

void JsonManager::saveNewObject(MediaItem* media){
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open file:" << filePath;
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError; //to check parsin errors
    QJsonDocument document = QJsonDocument::fromJson(data, &parseError); //to parse the data and save parsing errors

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << parseError.errorString();
        return;
    }

    QJsonArray jsonArray = document.array();
    QJsonObject obj = media->accept(new JsonVisitor());
    jsonArray.push_back(obj);
    QJsonDocument newDocument(jsonArray);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open file:" << filePath;
        return;
    }

    file.write(newDocument.toJson());
    file.close();
}

void JsonManager::DeleteObject(MediaItem* media){
    std::string title= media->getTitle();
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open file:" << filePath;
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError; //to check parsin errors
    QJsonDocument document = QJsonDocument::fromJson(data, &parseError); //to parse the data and save parsing errors

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << parseError.errorString();
        return;
    }

    QJsonArray jsonArray = document.array();
    for (int i = 0; i < jsonArray.size(); ++i) {
        QJsonValue value = jsonArray.at(i);
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            if (obj["Title"].toString().toStdString() == title) {//-----------------------------------------------------------------------------solo il titolo? (no per, ad esempio, episodi)
                jsonArray.removeAt(i);
                break;
            }
        }
    }

    QJsonDocument newDocument(jsonArray);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open file:" << filePath;
        return;
    }

    file.write(newDocument.toJson());
    file.close();

}

void JsonManager::ModifyObject(MediaItem* media, std::vector<std::pair<std::string,std::string>>& changes){//check solo col titolo...TODO-----------------------------------------------------------------------------
    std::string title= media->getTitle();
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open file:" << filePath;
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError; //to check parsin errors
    QJsonDocument document = QJsonDocument::fromJson(data, &parseError); //to parse the data and save parsing errors

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << parseError.errorString();
        return;
    }

    QJsonArray jsonArray = document.array();
    for (int i = 0; i < jsonArray.size(); ++i) {
        QJsonValue value = jsonArray.at(i);
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            if (obj["Title"].toString().toStdString() == title) {
                for(auto change : changes){
                    obj[QString::fromStdString(change.first)] = QString::fromStdString(change.second);
                }
                jsonArray.replace(i, obj);
            }
            break;
        }
    }
    

    QJsonDocument newDocument(jsonArray);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open file:" << filePath;
        return;
    }

    file.write(newDocument.toJson());
    file.close();
}

