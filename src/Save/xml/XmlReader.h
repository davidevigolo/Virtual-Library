#include <qxmlstream.h>
#include <MediaItem.h>
#include <Readable.h>
#include <Book.h>
#include <Article.h>
#include <Film.h>
#include <AudioVisual.h>
#include <Music.h>
#include <Podcast.h>

class XmlReader{
public:
    static MediaItem* readMediaItem(QXmlStreamReader& xmlReader);
    static Book* readBook(QXmlStreamReader& xmlReader);
    static Article* readArticle(QXmlStreamReader& xmlReader);
    static Film* readFilm(QXmlStreamReader& xmlReader);
    static Readable* readReadable(QXmlStreamReader& xmlReader);
    static AudioVisual* readAudioVisual(QXmlStreamReader& xmlReader);
    static Podcast* readPodcast(QXmlStreamReader& xmlReader);
    static Music* readMusic(QXmlStreamReader& xmlReader);
};