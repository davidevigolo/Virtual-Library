#pragma once
#include <Visitor.h>
#include <QGridLayout>
#include <Book.h>
#include <Article.h>
#include <Film.h>
#include <Podcast.h>
#include <Music.h>

/*
    GridVisitor is a concrete visitor that is used to display the items in a grid layout.
    It is used to display the items in the item window of the application.
*/
class GridVisitor : public Visitor {
    private:
        QWidget* widget;
        QGridLayout* grid;
    public:
        GridVisitor(QWidget* widget);
        virtual void visit(MediaItem* media) override;
        virtual void visit(Readable* readable) override;
        virtual void visit(AudioVisual* audioVisual) override;
        virtual void visit(Article* articles) override;
        virtual void visit(Book* book) override;
        virtual void visit(Film* film) override;
        virtual void visit(Podcast* podcast) override;
        virtual void visit(Music* music) override;
};