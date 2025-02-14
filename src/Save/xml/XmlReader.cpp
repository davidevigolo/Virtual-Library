#include "XmlReader.h"

MediaItem *XmlReader::read(QXmlStreamReader* xmlReader)
{
    auto className = xmlReader->name();

    std::vector<std::string> tags;
    QMap<QString, QString> *attributes = new QMap<QString, QString>();
    while (xmlReader->tokenType() != QXmlStreamReader::EndElement)
    {
        xmlReader->readNext(); // Two times since each xml entry has also a closing tag
        QString name = xmlReader->name().toString();
        qDebug() << "Name: ";
        qDebug() << name;
        if (name == "Tags")
        {
            while (!(xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == "Tags"))
            {
                xmlReader->readNext();
                if (xmlReader->tokenType() == QXmlStreamReader::StartElement && xmlReader->name() == "Tag")
                {
                    tags.push_back(xmlReader->readElementText().toStdString());
                }
            }
        }
        else
        {
            if (xmlReader->tokenType() == QXmlStreamReader::StartElement)
            {
                QString value = xmlReader->readElementText();
                attributes->insert(name, value);
                qDebug() << "Value: " << value;
            }
        }
    }
        

    if (className == "Article")
    {
        return new Article(
            attributes->value("Title").toStdString(),
            attributes->value("Author").toStdString(),
            attributes->value("ReleaseDate").toStdString(),
            attributes->value("ProductionHouse").toStdString(),
            attributes->value("Genre").toStdString(),
            tags,
            attributes->value("Format").toStdString(),
            attributes->value("Language").toStdString(),
            attributes->value("Used").toStdString(),
            attributes->value("Edition").toStdString(),
            attributes->value("Pages").toUInt(),
            attributes->value("Publisher").toStdString(),
            attributes->value("Image").toStdString());
    }
    else if (className == "Book")
    {
        return new Book(
            attributes->value("Title").toStdString(),
            attributes->value("Author").toStdString(),
            attributes->value("ReleaseDate").toStdString(),
            attributes->value("ProductionHouse").toStdString(),
            attributes->value("Genre").toStdString(),
            tags,
            attributes->value("Format").toStdString(),
            attributes->value("Language").toStdString(),
            attributes->value("Used").toStdString(),
            attributes->value("Edition").toStdString(),
            attributes->value("Pages").toUInt(),
            attributes->value("ISBN").toUInt(),
            attributes->value("Image").toStdString());
    }
    else if (className == "Film")
    {
        return new Film(
            attributes->value("Title").toStdString(),
            attributes->value("Author").toStdString(),
            attributes->value("ReleaseDate").toStdString(),
            attributes->value("ProductionHouse").toStdString(),
            attributes->value("Genre").toStdString(),
            tags,
            attributes->value("Format").toStdString(),
            attributes->value("Language").toStdString(),
            attributes->value("Used").toStdString(),
            attributes->value("Duration").toUInt(),
            attributes->value("Tecnic").toStdString(),
            attributes->value("Framerate").toDouble(),
            attributes->value("Director").toStdString(),
            attributes->value("Image").toStdString());
    }
    else if (className == "Music")
    {
        return new Music(
            attributes->value("Title").toStdString(),
            attributes->value("Author").toStdString(),
            attributes->value("ReleaseDate").toStdString(),
            attributes->value("ProductionHouse").toStdString(),
            attributes->value("Genre").toStdString(),
            tags,
            attributes->value("Format").toStdString(),
            attributes->value("Language").toStdString(),
            attributes->value("Used").toStdString(),
            attributes->value("Duration").toUInt(),
            attributes->value("Album").toStdString());
    }
    else if (className == "Podcast")
    {
        return new Podcast(
            attributes->value("Title").toStdString(),
            attributes->value("Author").toStdString(),
            attributes->value("ReleaseDate").toStdString(),
            attributes->value("ProductionHouse").toStdString(),
            attributes->value("Genre").toStdString(),
            tags,
            attributes->value("Format").toStdString(),
            attributes->value("Language").toStdString(),
            attributes->value("Used").toStdString(),
            attributes->value("Duration").toUInt(),
            attributes->value("Episodes").toUInt(),
            attributes->value("Image").toStdString());
    }
    else
    {
        qWarning() << "Unknown class name: " << className;
        return nullptr;
    }
}
