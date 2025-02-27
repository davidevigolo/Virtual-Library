#pragma once
#include <QVector>
#include <FieldWidget.h>
#include <Article.h>
#include <Book.h>
#include <Film.h>
#include <Music.h>
#include <Podcast.h>

/*This function save the changes done on the 
    field widget to the actual item*/

class EditMaker{
public:
    EditMaker();
    void makeEdit(FieldWidget* fieldWidget, MediaItem* item);
};