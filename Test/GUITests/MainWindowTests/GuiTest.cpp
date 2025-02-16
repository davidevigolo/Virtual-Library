
#include <QApplication>
#include <QWidget>
#include <ButtonWidget.h>
#include <Article.h>
#include <QVector>
#include <Book.h>
#include <MainDisplay.h>
#include <JsonManager.h>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    JsonManager json("test.json");
    
    QVector<MediaItem*> items = json.load();
    MainDisplay mainDisplay;
    mainDisplay.setAreas(items);
    mainDisplay.show();
    return app.exec();
}
