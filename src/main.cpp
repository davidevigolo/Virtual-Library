#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.setWindowTitle("Virtual Library");
    mainWindow.resize(800, 600);
    mainWindow.show();

    return app.exec();
}