#include <MainWindow.h>
#include <QLayout>
#include <QTextEdit>
#include <XmlManager.h>
#include <SearchBar.h>
#include <TopMenu.h>
#include <QFileDialog>
#include <ManagerFactory.h>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), mainDisplay(this)
{
    TopMenu *menuBar = new TopMenu(this);

    QObject::connect(menuBar->getNewFileAction(), &QAction::triggered, this, &MainWindow::loadFromFile);
    QObject::connect(menuBar->getExitAction(), &QAction::triggered, qApp, &QApplication::quit);
    QObject::connect(menuBar->getSaveAsAction(), &QAction::triggered, this, &MainWindow::saveToFile);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMenuBar(menuBar);
    SearchBar *searchBar = new SearchBar(this);

    connect(this, &MainWindow::itemsLoaded, &mainDisplay, &MainDisplay::setAreas); // Connect itemsLoaded signal to  mainDisplay setAreas to update the view

    mainLayout->addWidget(searchBar);
    mainLayout->addWidget(&mainDisplay);
    setLayout(mainLayout);

    setWindowTitle("Test Application");
    setStyleSheet("background-color: gray;");
}

void MainWindow::loadFromFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select File", "", "XML Files (*.xml);;JSON Files (*.json)");
    if (!filePath.isEmpty())
    {
        FileManager *fileManager = ManagerFactory(filePath).create();
        if (!fileManager) qErrnoWarning("Che cazzo è sto file porcoddio io accetto solo xml e json");
        mediaItems = fileManager->load();
        delete fileManager;
        emit itemsLoaded(mediaItems);
    }
}

void MainWindow::saveToFile()
{
}