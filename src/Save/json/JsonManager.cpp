#include "JsonManager.h"
#include "JsonVisitor.h"
JsonManager::~JsonManager() {}

std::vector<std::string> JsonManager::JsonArrToVec(const QJsonArray &array) const
{ // Convert a QJsonArray to a std::vector<std::string>
    std::vector<std::string> vec;
    for (const QJsonValue &value : array)
    {
        vec.push_back(value.toString().toStdString()); // Converte il valore in std::string
    }
    return vec;
}

MediaItem *JsonManager::ObjectLoader(const QString &className, const QJsonObject &obj) const
{ // create a media item from a json object
    MediaItem *media = nullptr;
    if (className == "Article")
    {
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
            obj["Publisher"].toString().toStdString(),
            obj["Image"].toString().toStdString());
    } else if(className == "Book"){
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
            obj["ISBN"].toInt(),
            obj["Image"].toString().toStdString());
    } else if (className == "Film"){
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
            obj["Duration"].toInt(),
            obj["Technique"].toString().toStdString(),
            obj["Framerate"].toDouble(),
            obj["Director"].toString().toStdString(),
            obj["Image"].toString().toStdString());
    } else if (className == "Music"){
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
            obj["Duration"].toInt(),
            obj["Album"].toString().toStdString(),
            obj["Image"].toString().toStdString());
    } else if (className == "Podcast"){
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
            obj["Duration"].toInt(),
            obj["Episodes"].toInt(),
            obj["Image"].toString().toStdString());
    }
    return media;
}

QVector<MediaItem *> JsonManager::load() const
{
    QVector<MediaItem *> Library; // create the vector of readen objects
    QFile file(filePath);         // load the file

    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Couldn't open file:" << filePath;
        return Library;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;                                          // to check parsin errors
    QJsonDocument document = QJsonDocument::fromJson(data, &parseError); // to parse the data and save parsing errors

    if (parseError.error != QJsonParseError::NoError)
    {
        qWarning() << "JSON parse error:" << parseError.errorString();
        return Library;
    }

    QJsonArray jsonArray = document.array();
    for (const QJsonValue &value : jsonArray)
    {
        if (value.isObject())
        {
            QJsonObject obj = value.toObject();              // save the object information
            if (obj.contains("Class")) {
                QString className = obj["Class"].toString();     // save the class information
                MediaItem* media = ObjectLoader(className, obj); // create the media item
                if (media != nullptr) {
                    Library.push_back(media); // add the created object to the vector
                }
            } else {
                qWarning() << "Object in JSON document missing 'Class' field";
            }
            
        }
    }

    return Library;
}

void JsonManager::save(QVector<MediaItem*>& Library) const
{
    QFile file(filePath);

    JsonVisitor visitor = JsonVisitor();
    QJsonArray jsonArray;

    for (auto media : Library)
    {
        media->accept(&visitor);
        jsonArray.push_back(visitor.getObject());
    }

    QJsonDocument newDocument(jsonArray);

    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning() << "Couldn't open file:" << filePath;
        return;
    }
    file.write(newDocument.toJson());
    file.close();
}

void JsonManager::setPath(const QString &path)
{
    filePath = path;
}

QString JsonManager::getPath() const
{
    return filePath;
}