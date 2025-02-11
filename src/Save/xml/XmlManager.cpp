#include "XmlManager.h"
#include <qfile.h>
#include <QXmlStreamWriter>
#include "XmlReader.h"


void XmlManager::save(std::vector<MediaItem*>& media)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        throw std::runtime_error("Could not open file for writing");
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("MediaItems");

    for (MediaItem* item : media) {
        XmlVisitor xmlVisitor(xmlWriter);
        item->accept(&xmlVisitor);
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}

QVector<MediaItem*> XmlManager::load()
{
    QVector<MediaItem*> result;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("Could not open file for reading");
    }

    QXmlStreamReader xmlReader(&file);
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        if (token == QXmlStreamReader::StartDocument) {
            continue;
        }

        if (token == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == "MediaItems") {
                continue;
            }

            auto elementName = xmlReader.name();
            xmlReader.readNextStartElement();
            if (elementName == QStringLiteral("MediaItem")) {
                result.push_back(XmlReader::readMediaItem(xmlReader));
            } else if (elementName == QStringLiteral("Book")) {
                result.push_back(XmlReader::readBook(xmlReader));
            } else if (elementName == QStringLiteral("Article")) {
                result.push_back(XmlReader::readArticle(xmlReader));
            } else if (elementName == QStringLiteral("Film")) {
                result.push_back(XmlReader::readFilm(xmlReader));
            } else if (elementName == QStringLiteral("Podcast")) {
                result.push_back(XmlReader::readPodcast(xmlReader));
            } else if (elementName == QStringLiteral("Music")) {
                result.push_back(XmlReader::readMusic(xmlReader));
            } else if (elementName == QStringLiteral("AudioVisual")) {
                result.push_back(XmlReader::readAudioVisual(xmlReader));
            } else if (elementName == QStringLiteral("Readable")) {
                result.push_back(XmlReader::readReadable(xmlReader));
            }
            
            else {
                throw std::runtime_error("Unknown element type"); //catch and display invalid file
            }
        }
    }

    file.close();
    return result;
}
