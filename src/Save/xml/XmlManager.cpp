#include "XmlManager.h"
#include <qfile.h>
#include <QXmlStreamWriter>
#include "XmlReader.h"
#include "XmlVisitor.h"

void XmlManager::save(std::vector<MediaItem *> &media)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        throw std::runtime_error("Could not open file for writing");
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
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

QVector<MediaItem *> XmlManager::load()
{
    QVector<MediaItem *> result;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        throw std::runtime_error("Could not open file for reading");
    }

    QXmlStreamReader xmlReader(&file);
    while (!xmlReader.atEnd() && !xmlReader.hasError())
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        qDebug() << xmlReader.name();
        qDebug() << xmlReader.readElementText();
        if (token == QXmlStreamReader::StartDocument)
        {
            continue;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xmlReader.name() == "MediaItems")
            {
                continue;
            }

            result.push_back(XmlReader::read(&xmlReader));
        }
        else
        {
            xmlReader.readNext();
        }
    }

    file.close();
    return result;
}
