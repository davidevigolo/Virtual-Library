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
    static MediaItem* read(QXmlStreamReader* xmlReader);
};