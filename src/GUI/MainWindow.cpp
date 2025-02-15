#include <MainWindow.h>
#include <QLayout>
#include <QTextEdit>
#include <XmlManager.h>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), mainDisplay(this)
{
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu("File", menuBar);
    QAction *exitAction = new QAction("Exit", fileMenu);
    fileMenu->addAction(exitAction);
    QAction *newAction = new QAction("New", fileMenu);
    fileMenu->addAction(newAction);
    menuBar->addMenu(fileMenu);

    QObject::connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    QObject::connect(newAction, &QAction::triggered, this, &MainWindow::loadFromFile);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMenuBar(menuBar);

    QHBoxLayout *searchLayout = new QHBoxLayout(this);
    QTextEdit *searchTextEdit = new QTextEdit;
    searchTextEdit->setPlaceholderText("Search...");
    QPushButton *searchButton = new QPushButton("Search");
    searchTextEdit->setFixedHeight(30);
    searchLayout->addWidget(searchTextEdit);
    searchLayout->addWidget(searchButton);

    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(&mainDisplay);
    setLayout(mainLayout);

    setWindowTitle("Test Application");
    setStyleSheet("background-color: gray;");
}

void MainWindow::loadFromFile()
{
    FileManager *fileManager = new XmlManager("test.xml"); // This is made just for testing purposes
    mediaItems = fileManager->load();
    mainDisplay.setItems(mediaItems);
}