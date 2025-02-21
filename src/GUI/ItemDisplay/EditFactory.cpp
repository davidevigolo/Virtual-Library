#include <EditFactory.h>
#include <iostream>
#include <QDebug>

EditFactory::EditFactory(){}

void EditFactory::makeEdit(FieldWidget* fieldWidget, MediaItem* item){
    if(fieldWidget->getFieldName() == "Title"){
        item->setTitle(fieldWidget->getLineEditValue().toStdString());
    }else if(fieldWidget->getFieldName() == "Author"){
        item->setAuthor(fieldWidget->getLineEditValue().toStdString());
    }else if(fieldWidget->getFieldName() == "Release Date"){
        item->setReleaseDate(fieldWidget->getLineEditValue().toStdString());
    }else if(fieldWidget->getFieldName() == "Production House"){
        item->setProductionHouse(fieldWidget->getLineEditValue().toStdString());
    }else if(fieldWidget->getFieldName() == "Genre"){
        item->setGenre(fieldWidget->getLineEditValue().toStdString());
    }else if(fieldWidget->getFieldName() == "Tags"){
        QStringList tags = fieldWidget->getLineEditValue().split(",");
        std::vector<std::string> tagList;
        for (const QString& tag : tags) {
            tagList.push_back(tag.trimmed().toStdString());
        }
        item->setTags(tagList);
    }else if(fieldWidget->getFieldName() == "Format"){
        item->setFormat(fieldWidget->getLineEditValue().toStdString());
    }else if(fieldWidget->getFieldName() == "Language"){
        item->setLanguage(fieldWidget->getLineEditValue().toStdString());
    }else if(fieldWidget->getFieldName() == "Used"){
        item->setUsed(fieldWidget->getLineEditValue().toStdString());
    }else if(fieldWidget->getFieldName() == "Edition"){
        static_cast<Readable*>(item)->setEdition(fieldWidget->getLineEditValue().toStdString());
    }else if(fieldWidget->getFieldName() == "Pages"){
        static_cast<Readable*>(item)->setPages(fieldWidget->getSpinBoxValue());
    }else if(fieldWidget->getFieldName() == "Publisher"){
        static_cast<Article*>(item)->setPublisher(fieldWidget->getLineEditValue().toStdString());
    }else if(fieldWidget->getFieldName() == "ISBN"){
        static_cast<Book*>(item)->setISBN(fieldWidget->getSpinBoxValue());
    }else if(fieldWidget->getFieldName() == "Duration"){
        static_cast<AudioVisual*>(item)->setDuration(fieldWidget->getSpinBoxValue());
    }else if(fieldWidget->getFieldName() == "Technique"){
        static_cast<Film*>(item)->setTechnique(fieldWidget->getLineEditValue().toStdString());
    }else if(fieldWidget->getFieldName() == "Framerate"){
        static_cast<Film*>(item)->setFramerate(fieldWidget->getDoubleSpinBoxValue());
    }else if(fieldWidget->getFieldName() == "Director"){
        static_cast<Film*>(item)->setDirector(fieldWidget->getLineEditValue().toStdString());
    }else if(fieldWidget->getFieldName() == "Album"){
        static_cast<Music*>(item)->setAlbum(fieldWidget->getLineEditValue().toStdString());
    }else if(fieldWidget->getFieldName() == "Episode"){
        static_cast<Podcast*>(item)->setEpisode(fieldWidget->getSpinBoxValue());
    }
}