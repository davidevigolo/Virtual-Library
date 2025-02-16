#include "XmlReader.h"
#include <iostream>

MediaItem *XmlReader::read(QXmlStreamReader* xmlReader)
{
    // Dopo aver letto StartDocument, siamo pronti a lavorare con gli StartElement
    QString className = xmlReader->name().toString();
    std::vector<std::string> tags;
    QMap<QString, QString> *attributes = new QMap<QString, QString>();

    // Continua finché non troviamo l'elemento di chiusura per questa classe
    if(xmlReader->hasError()) {
        qWarning() << "Error occurred during XML parsing: " << xmlReader->errorString();
        delete attributes;
        return nullptr;
    }   
    if(xmlReader->atEnd()) {
        qWarning() << "End of file reached";
        delete attributes;
        return nullptr;
    }
    while (!xmlReader->atEnd() && !xmlReader->hasError()) {
        if (xmlReader->readNext() == QXmlStreamReader::StartElement) {
            QString name = xmlReader->name().toString();
            qDebug() << "Start element: " << name;

            if (name == "Tags") {
                // Gestiamo i tag all'interno di <Tags>
                while (!(xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == "Tags")) {
                    xmlReader->readNext();
                    if (xmlReader->tokenType() == QXmlStreamReader::StartElement && xmlReader->name() == "Tag") {
                        // Legge il testo del tag <Tag>
                        tags.push_back(xmlReader->readElementText().toStdString());
                    }
                }
            } else {
                // Gestiamo i tag con dati di testo
                if (xmlReader->tokenType() == QXmlStreamReader::StartElement) {
                    QString elementName = xmlReader->name().toString();
                    xmlReader->readNext(); // Avanza al token successivo (probabilmente Characters)
                    if (xmlReader->tokenType() == QXmlStreamReader::Characters) {
                        // Memorizza i dati di testo per il tag
                        qDebug() << elementName << ":" << xmlReader->text().toString();
                        attributes->insert(elementName, xmlReader->text().toString());
                    }
                }
            }
        }
        else {
            qDebug() << "Token type: " << xmlReader->tokenType();
        }

        // Aggiungi controllo per eventuali errori XML
        if (xmlReader->hasError()) {
            qWarning() << "Error occurred during XML parsing: " << xmlReader->errorString();
            delete attributes;
            return nullptr;
        }

        // Verifica se siamo all'elemento di chiusura per questa classe
        if (xmlReader->tokenType() == QXmlStreamReader::EndElement && xmlReader->name() == className) {
            break;
        }
    }

    // Crea e restituisci l'oggetto corretto in base al nome della classe
    MediaItem* result = nullptr;
    if (className == "Article") {
        result = new Article(
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
    else if (className == "Book") {
        result = new Book(
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
    else if (className == "Film") {
        result = new Film(
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
    else if (className == "Music") {
        result = new Music(
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
    else if (className == "Podcast") {
        result = new Podcast(
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
    else {
        qWarning() << "Unknown class name: " << className;
    }

    delete attributes;
    return result;
}
