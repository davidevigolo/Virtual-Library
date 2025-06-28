#include <QApplication>
#include "GUI/MainWindow.h"
#include <Settings.h>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Settings settings; // Load settings from file
    MainWindow window;
    window.resize(1280,720);
    window.show();

    return app.exec();
}