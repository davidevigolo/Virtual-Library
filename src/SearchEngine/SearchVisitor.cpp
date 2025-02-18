#include <SearchVisitor.h>
#include <iostream>
#include <algorithm>

SearchVisitor::SearchVisitor(const QString &query) : query(query), points(0), pointsValue{
                                                                                  {"Title", 10}, // mediaItem
                                                                                  {"Author", 5},
                                                                                  {"Release Date", 5},
                                                                                  {"Production House", 5},
                                                                                  {"Genre", 5},
                                                                                  {"Tags", 5},
                                                                                  {"Format", 5},
                                                                                  {"Language", 5},
                                                                                  
                                                                                  {"Edition", 5}, // Readable

                                                                                  {"Publisher", 5}, // Article

                                                                                  {"ISBN", 5}, // Book

                                                                                  {"Duration", 5}, // AudioVisual

                                                                                  {"Director", 5}, // Film
                                                                                  {"Tecnic", 5},

                                                                                  {"Album", 5}, // Music

                                                                                  {"Episode", 5} // Podcast
                                                                              } {};

int SearchVisitor::getPoints() const
{
    return points;
}

bool SearchVisitor::is_number(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c)
                                      { return !std::isdigit(c); }) == s.end();
}

bool SearchVisitor::compare(std::string str1, QString str2)
{
    return std::search(str1.begin(), str1.end(), str2.begin(), str2.end(),
                       [](char c1, QChar c2)
                       { return std::tolower(c1) == std::tolower(c2.toLatin1()); }) != str1.end();
}

void SearchVisitor::visit(const MediaItem *item)
{
    points = 0;
    if (compare(item->getTitle(), query))
    {
        points += pointsValue["Title"];
    }
    if (compare(item->getAuthor(), query))
    {
        points += pointsValue["Author"];
    }
    if (compare(item->getReleaseDate(), query))
    {
        points += pointsValue["Release Date"];
    }
    if (compare(item->getProductionHouse(), query))
    {
        points += pointsValue["Production House"];
    }
    if (compare(item->getGenre(), query))
    {
        points += pointsValue["Genre"];
    }
    if (compare(item->getLanguage(), query))
    {
        points += pointsValue["Language"];
    }
    if (compare(item->getFormat(), query))
    {
        points += pointsValue["Format"];
    }
    for (const auto &tag : item->getTags())
    {
        if (compare(tag, query))
        {
            points += pointsValue["Tags"];
        }
    }
}

void SearchVisitor::visit(const Readable *item)
{
    visit(static_cast<const MediaItem *>(item));
    if (compare(item->getEdition(), query))
    {
        points += pointsValue["Edition"];
    }
}

void SearchVisitor::visit(const AudioVisual *item)
{
    visit(static_cast<const MediaItem *>(item));
}

void SearchVisitor::visit(const Article *item)
{
    visit(static_cast<const Readable *>(item));
    if (compare(item->getPublisher(), query))
    {
        points += pointsValue["Publisher"];
    }
}

void SearchVisitor::visit(const Book *item)
{
    visit(static_cast<const Readable *>(item));
    if (!is_number(query.toStdString()))
    {
        return;
    }
    if (item->getISBN() == query.toUInt())
    {
        points += pointsValue["ISBN"];
    }
}

void SearchVisitor::visit(const Film *item)
{
    visit(static_cast<const AudioVisual *>(item));
    if (compare(item->getDirector(), query))
    {
        points += pointsValue["Director"];
    }
    if (compare(item->getTechnique(), query))
    {
        points += pointsValue["Tecnic"];
    }
}

void SearchVisitor::visit(const Podcast *item)
{
    visit(static_cast<const AudioVisual *>(item));
    if (!is_number(query.toStdString()))
    {
        return;
    }
    if (item->getEpisode() == query.toUInt())
    {
        points += pointsValue["Episode"];
    }
}

void SearchVisitor::visit(const Music *item)
{
    visit(static_cast<const AudioVisual *>(item));
    if (compare(item->getAlbum(), query))
    {
        points += pointsValue["Album"];
    }
}

void SearchVisitor::setQuery(const QString &query)
{
    this->query = query;
}

QString SearchVisitor::getQuery() const
{
    return query;
}
