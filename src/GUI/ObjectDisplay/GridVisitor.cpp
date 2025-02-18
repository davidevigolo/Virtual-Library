#include <GridVisitor.h>
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include <FieldWidget.h>

GridVisitor::GridVisitor(QWidget* widget) : widget(widget) , grid(new QGridLayout(widget)){}

void GridVisitor::visit(MediaItem* media) {
    FieldWidget *title = new FieldWidget("Title", QString::fromStdString(media->getTitle()), widget);
    FieldWidget *author = new FieldWidget("Author", QString::fromStdString(media->getAuthor()), widget);
    FieldWidget *releaseDate = new FieldWidget("Release Date", QString::fromStdString(media->getReleaseDate()), widget);
    FieldWidget *productionHouse = new FieldWidget("Production House", QString::fromStdString(media->getProductionHouse()), widget);
    FieldWidget *genre = new FieldWidget("Genre", QString::fromStdString(media->getGenre()), widget);
    FieldWidget *tags = new FieldWidget("Tags", media->getTags(), widget);
    FieldWidget *format = new FieldWidget("Format", QString::fromStdString(media->getFormat()), widget);
    FieldWidget *language = new FieldWidget("Language", QString::fromStdString(media->getLanguage()), widget);
    FieldWidget *used = new FieldWidget("Used", QString::fromStdString(media->getUsed()), widget);

    // title->setStyleSheet("border: 1px solid black");
    // author->setStyleSheet("border: 1px solid black");
    // releaseDate->setStyleSheet("border: 1px solid black");
    // productionHouse->setStyleSheet("border: 1px solid black");
    // genre->setStyleSheet("border: 1px solid black");
    // tags->setStyleSheet("border: 1px solid black");
    // format->setStyleSheet("border: 1px solid black");
    // language->setStyleSheet("border: 1px solid black");
    // used->setStyleSheet("border: 1px solid black");

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
    FieldWidget *edition = new FieldWidget("Edition", QString::fromStdString(readable->getEdition()), widget);
    FieldWidget *pages = new FieldWidget("Pages", QString::fromStdString(std::to_string(readable->getPages())), widget);

    grid->addWidget(edition, 5, 1);
    grid->addWidget(pages, 6, 0);
}

void GridVisitor::visit(Book* book) {
    visit(static_cast<Readable*>(book));
    FieldWidget *isbn = new FieldWidget("ISBN", QString::fromStdString(std::to_string(book->getISBN())), widget);

    grid->addWidget(isbn, 6, 1);
}

void GridVisitor::visit(Article* article) {
    visit(static_cast<Readable*>(article));
    FieldWidget *publisher = new FieldWidget("Publisher", QString::fromStdString(article->getPublisher()), widget);
    
    grid->addWidget(publisher, 6, 1);
    
}

void GridVisitor::visit(AudioVisual* audioVisual) {
    visit(static_cast<MediaItem*>(audioVisual));
    FieldWidget *duration = new FieldWidget("Duration", QString::fromStdString(std::to_string(audioVisual->getDuration())), widget);
    grid->addWidget(duration, 5, 1);
}

void GridVisitor::visit(Music* music) {
    visit(static_cast<AudioVisual*>(music));
    FieldWidget *album = new FieldWidget("Album", QString::fromStdString(music->getAlbum()), widget);
    grid->addWidget(album, 6, 0);
}

void GridVisitor::visit(Film* film) {
    visit(static_cast<AudioVisual*>(film));
    FieldWidget *director = new FieldWidget("Director", QString::fromStdString(film->getDirector()), widget);
    FieldWidget *tecnic = new FieldWidget("Tecnic", QString::fromStdString(film->getTecnic()), widget);
    FieldWidget *framerate = new FieldWidget("Framerate", QString::fromStdString(std::to_string(film->getFramerate())), widget);

    grid->addWidget(director, 6, 0);
    grid->addWidget(tecnic, 6, 1);
    grid->addWidget(framerate, 7, 0);
}

void GridVisitor::visit(Podcast* podcast) {
    visit(static_cast<AudioVisual*>(podcast));
    FieldWidget *episode = new FieldWidget("Episode", QString::fromStdString(std::to_string(podcast->getEpisode())), widget);

    grid->addWidget(episode, 6, 0);
}