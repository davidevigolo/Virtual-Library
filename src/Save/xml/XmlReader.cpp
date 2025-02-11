#include "XmlReader.h"

MediaItem* XmlReader::readMediaItem(QXmlStreamReader& xmlReader) {
    std::string title;
    std::string author;
    std::string releaseDate;
    std::string productionHouse;
    std::string genre;
    std::vector<std::string> tags;
    std::string format;
    std::string language;
    std::string used;

    while (xmlReader.tokenType() != QXmlStreamReader::EndElement) {
        qDebug() << xmlReader.name();
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == "Title") {
                title = xmlReader.readElementText().toStdString();
            } else if (xmlReader.name() == "Author") {
                author = xmlReader.readElementText().toStdString();
            } else if (xmlReader.name() == "ReleaseDate") {
                releaseDate = xmlReader.readElementText().toStdString();
            } else if (xmlReader.name() == "ProductionHouse") {
                productionHouse = xmlReader.readElementText().toStdString();
            } else if (xmlReader.name() == "Genre") {
                genre = xmlReader.readElementText().toStdString();
            } else if (xmlReader.name() == "Tags") {
                while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "Tags")) {
                    xmlReader.readNext();
                    if (xmlReader.tokenType() == QXmlStreamReader::StartElement && xmlReader.name() == "Tag") {
                        tags.push_back(xmlReader.readElementText().toStdString());
                    }
                }
            } else if (xmlReader.name() == "Format") {
                format = xmlReader.readElementText().toStdString();
            } else if (xmlReader.name() == "Language") {
                language = xmlReader.readElementText().toStdString();
            } else if (xmlReader.name() == "Used") {
                used = xmlReader.readElementText().toStdString();
            } else { // If the element is not recognized, means the reading should continue on a subclass reader
                return new MediaItem(title, author, releaseDate, productionHouse, genre, tags, format, language, used);
            }
            xmlReader.readNext();
            xmlReader.readNext();
        }else{
            xmlReader.readNext();
        }
    }

    return new MediaItem(title, author, releaseDate, productionHouse, genre, tags, format, language, used);
}

Readable* XmlReader::readReadable(QXmlStreamReader& xmlReader) {
    unsigned int pages;

    MediaItem* media = readMediaItem(xmlReader);
    std::string edition;
    while (xmlReader.tokenType() != QXmlStreamReader::EndElement) {
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == "Pages") {
                pages = xmlReader.readElementText().toUInt();
            } else if (xmlReader.name() == "Edition") {
                edition = xmlReader.readElementText().toStdString();
            } else {
                return new Readable(media, edition, pages);
            }
            xmlReader.readNext();
            xmlReader.readNext();
        }else{
            xmlReader.readNext();
        }
    }

    return new Readable(media, edition, pages);
}

Book* XmlReader::readBook(QXmlStreamReader& xmlReader) {
    unsigned int ISBN;

    Readable* media = readReadable(xmlReader);
    while (xmlReader.tokenType() != QXmlStreamReader::EndElement) {
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == "ISBN") {
                ISBN = xmlReader.readElementText().toUInt();
            } else {
                return new Book(media, ISBN);
            }
            xmlReader.readNext();
            xmlReader.readNext();
        }else{
            xmlReader.readNext();
        }
    }

    return new Book(media, ISBN);
}

Article* XmlReader::readArticle(QXmlStreamReader& xmlReader) {
    std::string publisher;

    Readable* media = readReadable(xmlReader);
    while (xmlReader.tokenType() != QXmlStreamReader::EndElement) {
        xmlReader.readNext();
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == "Publisher") {
                publisher = xmlReader.readElementText().toStdString();
            } else {
                return new Article(media, publisher);
            }
            xmlReader.readNext();
            xmlReader.readNext();
        }else{
            xmlReader.readNext();
        }
    }

    return new Article(media, publisher);
}

AudioVisual* XmlReader::readAudioVisual(QXmlStreamReader& xmlReader) {
    std::string duration;

    MediaItem* media = readMediaItem(xmlReader);
    qDebug() << "Reading audiovisual";
    qDebug() << xmlReader.name();
    qDebug() << xmlReader.tokenType();
    while (xmlReader.tokenType() != QXmlStreamReader::EndElement) {
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == "Duration") {
                duration = xmlReader.readElementText().toStdString();
            } else {
                return new AudioVisual(media, duration);
            }
            xmlReader.readNext();
            xmlReader.readNext();
        }else{
            xmlReader.readNext();
        }
    }

    return new AudioVisual(media, duration);
}

Film* XmlReader::readFilm(QXmlStreamReader& xmlReader) {
    std::string tecnic;
    double framerate;
    std::string director;

    AudioVisual* media = readAudioVisual(xmlReader);
    while (xmlReader.tokenType() != QXmlStreamReader::EndElement) {
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == "Tecnic") {
                tecnic = xmlReader.readElementText().toStdString();
            } else if (xmlReader.name() == "Framerate") {
                framerate = xmlReader.readElementText().toDouble();
            } else if (xmlReader.name() == "Director") {
                director = xmlReader.readElementText().toStdString();
            } else {
                return new Film(media, tecnic, framerate, director);
            }
            xmlReader.readNext();
            xmlReader.readNext();
        }else{
            xmlReader.readNext();
        }
    }

    return new Film(media, tecnic, framerate, director);
}

Podcast* XmlReader::readPodcast(QXmlStreamReader& xmlReader) {
    unsigned int episodes;

    AudioVisual* media = readAudioVisual(xmlReader);
    while (xmlReader.tokenType() != QXmlStreamReader::EndElement) {
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == "Episodes") {
                episodes = xmlReader.readElementText().toUInt();
            } else {
                return new Podcast(media, episodes);
            }
            xmlReader.readNext();
            xmlReader.readNext();
        }else{
            xmlReader.readNext();
        }
    }

    return new Podcast(media, episodes);
}

Music* XmlReader::readMusic(QXmlStreamReader& xmlReader) {
    std::string album;

    AudioVisual* media = readAudioVisual(xmlReader);
    while (xmlReader.tokenType() != QXmlStreamReader::EndElement) {
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == "Album") {
                album = xmlReader.readElementText().toStdString();
            } else {
                return new Music(media, album);
            }
            xmlReader.readNext();
            xmlReader.readNext();
        }else{
            xmlReader.readNext();
        }
    }

    return new Music(media, album);
}