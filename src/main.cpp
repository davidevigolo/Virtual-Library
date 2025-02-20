#include <QApplication>
#include "GUI/MainWindow.h"
#include <Settings.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    Settings settings; // Load settings from file
    window.resize(1280,720);
    window.show();

    return app.exec();
}