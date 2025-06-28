#include "XmlReader.h"
#include <qdom.h>

MediaItem *XmlReader::read(QDomNode &node)
{
    auto className = node.nodeName();
    auto attributes = node.toElement().childNodes();
    QMap<QString, QString> attributes_map;
    std::vector<std::string> tags;

    for (int i = 0; i < attributes.size(); i++)
    {
        QDomNode attribute = attributes.at(i);
        if (attribute.nodeName() == "Tags")
        {
            auto childs = attribute.childNodes();
            for (int j = 0; j < childs.size(); j++)
            {
                QDomNode tag = childs.at(j);
                tags.push_back(tag.toElement().text().toStdString());
            }
        }
        else
        {
            attributes_map.insert(attribute.nodeName(), attribute.toElement().text());
        }
    }

    if (className == "Article")
    {
        return new Article(
            attributes_map["Title"].toStdString(),
            attributes_map["Author"].toStdString(),
            attributes_map["ReleaseDate"].toStdString(),
            attributes_map["ProductionHouse"].toStdString(),
            attributes_map["Genre"].toStdString(),
            tags,
            attributes_map["Format"].toStdString(),
            attributes_map["Language"].toStdString(),
            attributes_map["Used"].toLower() == "true",
            attributes_map["Edition"].toStdString(),
            attributes_map["Pages"].toUInt(),
            attributes_map["Publisher"].toStdString(),
            attributes_map["Image"].toStdString());
    }
    else if (className == "Book")
    {
        return new Book(
            attributes_map["Title"].toStdString(),
            attributes_map["Author"].toStdString(),
            attributes_map["ReleaseDate"].toStdString(),
            attributes_map["ProductionHouse"].toStdString(),
            attributes_map["Genre"].toStdString(),
            tags,
            attributes_map["Format"].toStdString(),
            attributes_map["Language"].toStdString(),
            attributes_map["Used"].toLower() == "true",
            attributes_map["Edition"].toStdString(),
            attributes_map["Pages"].toUInt(),
            attributes_map["ISBN"].toUInt(),
            attributes_map["Image"].toStdString());
    }
    else if (className == "Film")
    {
        return new Film(
            attributes_map["Title"].toStdString(),
            attributes_map["Author"].toStdString(),
            attributes_map["ReleaseDate"].toStdString(),
            attributes_map["ProductionHouse"].toStdString(),
            attributes_map["Genre"].toStdString(),
            tags,
            attributes_map["Format"].toStdString(),
            attributes_map["Language"].toStdString(),
            attributes_map["Used"].toLower() == "true",
            attributes_map["Duration"].toUInt(),
            attributes_map["Technique"].toStdString(),
            attributes_map["Framerate"].toDouble(),
            attributes_map["Director"].toStdString(),
            attributes_map["Image"].toStdString());
        }
        else if (className == "Music")
        {
        return new Music(
            attributes_map["Title"].toStdString(),
            attributes_map["Author"].toStdString(),
            attributes_map["ReleaseDate"].toStdString(),
            attributes_map["ProductionHouse"].toStdString(),
            attributes_map["Genre"].toStdString(),
            tags,
            attributes_map["Format"].toStdString(),
            attributes_map["Language"].toStdString(),
            attributes_map["Used"].toLower() == "true",
            attributes_map["Duration"].toUInt(),
            attributes_map["Album"].toStdString(),
            attributes_map["Image"].toStdString());
        }
        else if (className == "Podcast")
        {
        return new Podcast(
            attributes_map["Title"].toStdString(),
            attributes_map["Author"].toStdString(),
            attributes_map["ReleaseDate"].toStdString(),
            attributes_map["ProductionHouse"].toStdString(),
            attributes_map["Genre"].toStdString(),
            tags,
            attributes_map["Format"].toStdString(),
            attributes_map["Language"].toStdString(),
            attributes_map["Used"].toLower() == "true",
            attributes_map["Duration"].toUInt(),
            attributes_map["Episode"].toUInt(),
            attributes_map["Image"].toStdString());
    }
    else {
        qWarning() << "Unknown class name: " << className;
        return nullptr;
    }
}
