#include <EditFactory.h>
#include <iostream>
#include <QDebug>

EditFactory::EditFactory(){}

void EditFactory::makeEdit(FieldWidget* fieldWidget, MediaItem* item){
    if(fieldWidget->getFieldName() == "Title"){
        item->setTitle(fieldWidget->getFieldValue().toString().toStdString());
    }else if(fieldWidget->getFieldName() == "Author"){
        item->setAuthor(fieldWidget->getFieldValue().toString().toStdString());
    }else if(fieldWidget->getFieldName() == "Release Date"){
        item->setReleaseDate(fieldWidget->getFieldValue().toString().toStdString());
    }else if(fieldWidget->getFieldName() == "Production House"){
        item->setProductionHouse(fieldWidget->getFieldValue().toString().toStdString());
    }else if(fieldWidget->getFieldName() == "Genre"){
        item->setGenre(fieldWidget->getFieldValue().toString().toStdString());
    }else if(fieldWidget->getFieldName() == "Tags"){
        QStringList tags = fieldWidget->getFieldValue().toString().split(",");
        std::vector<std::string> tagList;
        for (const QString& tag : tags) {
            tagList.push_back(tag.trimmed().toStdString());
        }
        item->setTags(tagList);
    }else if(fieldWidget->getFieldName() == "Format"){
        item->setFormat(fieldWidget->getFieldValue().toString().toStdString());
    }else if(fieldWidget->getFieldName() == "Language"){
        item->setLanguage(fieldWidget->getFieldValue().toString().toStdString());
    }else if(fieldWidget->getFieldName() == "Used"){
        item->setUsed(fieldWidget->getFieldValue().toBool());
    }else if(fieldWidget->getFieldName() == "Edition"){
        static_cast<Readable*>(item)->setEdition(fieldWidget->getFieldValue().toString().toStdString());
    }else if(fieldWidget->getFieldName() == "Pages"){
        static_cast<Readable*>(item)->setPages(fieldWidget->getFieldValue().toInt());
    }else if(fieldWidget->getFieldName() == "Publisher"){
        static_cast<Article*>(item)->setPublisher(fieldWidget->getFieldValue().toString().toStdString());
    }else if(fieldWidget->getFieldName() == "ISBN"){
        static_cast<Book*>(item)->setISBN(fieldWidget->getFieldValue().toInt());
    }else if(fieldWidget->getFieldName() == "Duration"){
        static_cast<AudioVisual*>(item)->setDuration(fieldWidget->getFieldValue().toInt());
    }else if(fieldWidget->getFieldName() == "Technique"){
        static_cast<Film*>(item)->setTechnique(fieldWidget->getFieldValue().toString().toStdString());
    }else if(fieldWidget->getFieldName() == "Framerate"){
        static_cast<Film*>(item)->setFramerate(fieldWidget->getFieldValue().toDouble());
    }else if(fieldWidget->getFieldName() == "Director"){
        static_cast<Film*>(item)->setDirector(fieldWidget->getFieldValue().toString().toStdString());
    }else if(fieldWidget->getFieldName() == "Album"){
        static_cast<Music*>(item)->setAlbum(fieldWidget->getFieldValue().toString().toStdString());
    }else if(fieldWidget->getFieldName() == "Episode"){
        static_cast<Podcast*>(item)->setEpisode(fieldWidget->getFieldValue().toInt());
    }
}