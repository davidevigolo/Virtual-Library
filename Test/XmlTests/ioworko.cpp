#include <QCoreApplication>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

void printMediaItems(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        return;
    }

    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError()) {
        if (xml.readNext() == QXmlStreamReader::StartElement) {
            if (xml.name() == "Book" || xml.name() == "Article" || xml.name() == "Film" || xml.name() == "Podcast" || xml.name() == "Music") {
                qDebug() << "Type:" << xml.name().toString();
                while (!(xml.tokenType() == QXmlStreamReader::EndElement && (xml.name() == "Book" || xml.name() == "Article" || xml.name() == "Film" || xml.name() == "Podcast" || xml.name() == "Music"))) {
                    if (xml.tokenType() == QXmlStreamReader::StartElement) {
                        QString elementName = xml.name().toString();
                        xml.readNext();
                        if (xml.tokenType() == QXmlStreamReader::Characters) {
                            qDebug() << elementName << ":" << xml.text().toString();
                        }
                    }
                    xml.readNext();
                }
                qDebug() << "-----------------------------";
            }
        }
    }

    if (xml.hasError()) {
        qDebug() << "XML error:" << xml.errorString();
    }

    file.close();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString filePath = "/home/kevin/Desktop/C++/qt/test.xml";
    printMediaItems(filePath);

    return a.exec();
}
