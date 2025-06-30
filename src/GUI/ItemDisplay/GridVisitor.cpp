#include <GridVisitor.h>
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include <FieldWidget.h>

GridVisitor::GridVisitor(QWidget* widget, QGridLayout* grid) : widget(widget), grid(grid) {}

/*
    * This function is used to visit a MediaItem object and display its fields in the grid layout.
    * @param media: the MediaItem object to be visited
*/
void GridVisitor::visit(MediaItem* media) {
    FieldWidget *title = new FieldWidget("Title", QString::fromStdString(media->getTitle()), TEXT, widget);
    FieldWidget *author = new FieldWidget("Author", QString::fromStdString(media->getAuthor()), TEXT, widget);
    FieldWidget *releaseDate = new FieldWidget("Release Date", QString::fromStdString(media->getReleaseDate()), TEXT, widget);
    FieldWidget *productionHouse = new FieldWidget("Production House", QString::fromStdString(media->getProductionHouse()), TEXT, widget);
    FieldWidget *genre = new FieldWidget("Genre", QString::fromStdString(media->getGenre()), TEXT, widget);
    QStringList tagsList;
    for (const auto& tag : media->getTags()) {
        tagsList << QString::fromStdString(tag);
    }
    FieldWidget *tags = new FieldWidget("Tags", tagsList, TAGS, widget);
    FieldWidget *format = new FieldWidget("Format", QString::fromStdString(media->getFormat()), TEXT, widget);
    FieldWidget *language = new FieldWidget("Language", QString::fromStdString(media->getLanguage()), TEXT, widget);
    FieldWidget *used = new FieldWidget("Used", media->getUsed(), BOOL, widget);

    grid->addWidget(title, 0, 0, 1, 2);
    grid->addWidget(author, 1, 0);
    grid->addWidget(releaseDate, 1, 1);
    grid->addWidget(productionHouse, 2, 0);
    grid->addWidget(genre, 2, 1);
    grid->addWidget(tags, 3, 0, 1, 2);
    grid->addWidget(format, 4, 0);
    grid->addWidget(language, 4, 1);
    grid->addWidget(used, 5, 0);

}

void GridVisitor::visit(Readable* readable) {
    visit(static_cast<MediaItem*>(readable));
    FieldWidget *edition = new FieldWidget("Edition", QString::fromStdString(readable->getEdition()), TEXT, widget);
    FieldWidget *pages = new FieldWidget("Pages", readable->getPages(), INTEGER, widget);

    grid->addWidget(edition, 5, 1);
    grid->addWidget(pages, 6, 0);
}

void GridVisitor::visit(Book* book) {
    visit(static_cast<Readable*>(book));
    FieldWidget *isbn = new FieldWidget("ISBN", book->getISBN(), INTEGER, widget);

    grid->addWidget(isbn, 6, 1);
}

void GridVisitor::visit(Article* article) {
    visit(static_cast<Readable*>(article));
    FieldWidget *publisher = new FieldWidget("Publisher", QString::fromStdString(article->getPublisher()),TEXT, widget);
    
    grid->addWidget(publisher, 6, 1);
    
}

void GridVisitor::visit(AudioVisual* audioVisual) {
    visit(static_cast<MediaItem*>(audioVisual));
    FieldWidget *duration = new FieldWidget("Duration", audioVisual->getDuration(), INTEGER, widget);
    grid->addWidget(duration, 6, 1);
}

void GridVisitor::visit(Music* music) {
    visit(static_cast<AudioVisual*>(music));
    FieldWidget *album = new FieldWidget("Album", QString::fromStdString(music->getAlbum()), TEXT, widget);
    grid->addWidget(album, 7, 0);
}

void GridVisitor::visit(Film* film) {
    visit(static_cast<AudioVisual*>(film));
    FieldWidget *director = new FieldWidget("Director", QString::fromStdString(film->getDirector()), TEXT, widget);
    FieldWidget *technique = new FieldWidget("Technique", QString::fromStdString(film->getTechnique()), TEXT, widget);
    FieldWidget *framerate = new FieldWidget("Framerate", film->getFramerate(), DOUBLE, widget);

    grid->addWidget(director, 7, 0);
    grid->addWidget(technique, 7, 1);
    grid->addWidget(framerate, 8, 0);
}

void GridVisitor::visit(Podcast* podcast) {
    visit(static_cast<AudioVisual*>(podcast));
    FieldWidget *episode = new FieldWidget("Episode", podcast->getEpisode(), INTEGER, widget);

    grid->addWidget(episode, 7, 0);
}