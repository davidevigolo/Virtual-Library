#include <MainWindow.h>
#include <QLayout>
#include <QTextEdit>
#include <XmlManager.h>
#include <SearchBar.h>
#include <TopMenu.h>
#include <QFileDialog>
#include <ManagerFactory.h>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), fileManager(nullptr), searchEngine()
{
    TopMenu *menuBar = new TopMenu(this);

    SearchBar *searchBar = new SearchBar(this);

    MainDisplay *mainDisplay = new MainDisplay(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QObject::connect(menuBar, &TopMenu::NewFileSignal, this, &MainWindow::loadFromFile);
    QObject::connect(menuBar, &TopMenu::SaveSignal, this, &MainWindow::save);
    QObject::connect(menuBar, &TopMenu::SaveAsSignal, this, &MainWindow::saveToFile);


    mainLayout->setMenuBar(menuBar);

    connect(this, &MainWindow::itemsLoaded, mainDisplay, &MainDisplay::setAreas); // Connect itemsLoaded signal to  mainDisplay setAreas to update the view

    mainLayout->addWidget(searchBar);

    connect(searchBar, &SearchBar::queryChanged, this, &MainWindow::search); // Connect search signal to mainDisplay search to filter the items

    mainLayout->addWidget(mainDisplay);

    setLayout(mainLayout);

    setWindowTitle("Test Application");
    setStyleSheet("background-color: gray;");
}

void MainWindow::loadFromFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select File", "", "XML Files (*.xml *.json);;All Files (*)");
    if (!filePath.isEmpty())
    {
        fileManager = ManagerFactory(filePath).create();
        if (!fileManager)
            qErrnoWarning("File type not supported");
        mediaItems = fileManager->load();
        emit itemsLoaded(mediaItems);
    }
}

void MainWindow::save()
{
    if(fileManager)
        fileManager->save(mediaItems);
    else
        saveToFile();
}

void MainWindow::saveToFile()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    QString strFile = dialog.getSaveFileName(NULL, "Create New File", "", "");
    fileManager = ManagerFactory(strFile).create();
    fileManager->setPath(strFile);
    fileManager->save(mediaItems);
}

void MainWindow::search(QString query)
{
    QVector<MediaItem*> filteredItems = searchEngine.search(query, mediaItems);
    emit itemsLoaded(filteredItems);   
}   