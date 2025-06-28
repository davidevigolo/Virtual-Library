#include "XmlManager.h"
#include <qfile.h>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include "XmlReader.h"
#include "XmlVisitor.h"

void XmlManager::save(QVector<MediaItem*>& media) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        throw std::runtime_error("Could not open file for writing");
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true); // Set auto formatting to false
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("MediaItems");

    for (MediaItem *item : media)
    {
        XmlVisitor xmlVisitor(xmlWriter);
        item->accept(&xmlVisitor);
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}

QVector<MediaItem *> XmlManager::load() const
{
    QVector<MediaItem *> result;
    QFile file(filePath);
    QDomDocument document;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw std::runtime_error("Could not open file for reading");
    }
    if(!document.setContent(&file)){
        throw std::runtime_error("File content is invalid or corrupted");
    }

    QDomElement root =  document.firstChildElement();
    QDomNodeList mediaItems = root.elementsByTagName("MediaItem");
    for (int i = 0; i < mediaItems.size(); i++)
    {
        QDomNode node = mediaItems.at(i).firstChild();
        XmlReader reader;
        result.push_back(reader.read(node));
    }


    file.close();
    return result;
}

void XmlManager::setPath(const QString& path){
    filePath = path;
}

QString XmlManager::getPath() const{
    return filePath;
}