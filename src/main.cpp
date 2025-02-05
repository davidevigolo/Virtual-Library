#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Virtual Library");
    mainWindow.resize(800, 600);
    mainWindow.show();

    return app.exec();
}