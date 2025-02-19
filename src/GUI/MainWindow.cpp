#include <MainWindow.h>
#include <QLayout>
#include <QTextEdit>
#include <XmlManager.h>
#include <SearchBar.h>
#include <TopMenu.h>
#include <QFileDialog>
#include <ManagerFactory.h>
#include <iostream>
#include <ItemDisplay.h>
#include <qmenu.h>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), fileManager(nullptr), searchEngine()
{
    this->setStyleSheet("background-color: #1e2124; color: white;");
    TopMenu *menuBar = new TopMenu(this);

    MainDisplay *mainDisplay = new MainDisplay(this);
    connect(mainDisplay, &MainDisplay::itemButtonClicked, this, &MainWindow::onButtonClicked);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QObject::connect(menuBar, &TopMenu::NewFileSignal, this, &MainWindow::loadFromFile);
    QObject::connect(menuBar, &TopMenu::SaveSignal, this, &MainWindow::save);
    QObject::connect(menuBar, &TopMenu::SaveAsSignal, this, &MainWindow::saveToFile);

    mainLayout->setMenuBar(menuBar);

    connect(this, &MainWindow::itemsLoaded, mainDisplay, &MainDisplay::setAreas); // Connect itemsLoaded signal to  mainDisplay setAreas to update the view

    createHeader();
    
    mainLayout->addWidget(mainDisplay);

    setLayout(mainLayout);

    setWindowTitle("Virtual Library");
}

void MainWindow::loadFromFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select File", "", "Files (*.xml *.json);;All Files (*)");
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
    if (fileManager)
        fileManager->save(mediaItems);
    else
        saveToFile();
}

void MainWindow::saveToFile()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    QString strFile = dialog.getSaveFileName(NULL, "Create New File", "", "");
    if (strFile.isEmpty())
        return;
    fileManager = ManagerFactory(strFile).create();
    fileManager->setPath(strFile);
    fileManager->save(mediaItems);
}

void MainWindow::search(QString query)
{
    QVector<MediaItem *> filteredItems = searchEngine.search(query, mediaItems);
    emit itemsLoaded(filteredItems);
}

void MainWindow::onButtonClicked(MediaItem *item)
{
    clearView();
    ItemDisplay *itemDisplay = new ItemDisplay(item, this);

    connect(itemDisplay, &ItemDisplay::itemDeleted, this, &MainWindow::onItemDeleted);
    connect(itemDisplay, &ItemDisplay::itemDisplayClosed, this, &MainWindow::onItemDisplayClosed);

    if (layout())
        layout()->addWidget(itemDisplay);
}

void MainWindow::onItemDeleted(MediaItem *item)
{
    mediaItems.removeOne(item);
    onItemDisplayClosed();
    emit itemsLoaded(mediaItems);
}

void MainWindow::onItemDisplayClosed()
{
    clearView();
    createHeader();
    MainDisplay *mainDisplay = new MainDisplay(this);
    connect(mainDisplay, &MainDisplay::itemButtonClicked, this, &MainWindow::onButtonClicked);
    connect(this, &MainWindow::itemsLoaded, mainDisplay, &MainDisplay::setAreas);
    layout()->addWidget(mainDisplay);
    emit itemsLoaded(mediaItems);
}

void MainWindow::onNewItemButtonClicked()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
        return;

    QString itemType = action->text();
    MediaItem *item = nullptr;

    if (itemType == "Article")
        item = new Article();
    else if (itemType == "Book")
        item = new Book();
    else if (itemType == "Film")
        item = new Film();
    else if (itemType == "Music")
        item = new Music();
    else if (itemType == "Podcast")
        item = new Podcast();
    else
        return;

    if (item)
        mediaItems.append(item);
    clearView();

    ItemDisplay *itemDisplay = new ItemDisplay(item, this);

    connect(itemDisplay, &ItemDisplay::itemDeleted, this, &MainWindow::onItemDeleted);
    connect(itemDisplay, &ItemDisplay::itemDisplayClosed, this, &MainWindow::onItemDisplayClosed);

    layout()->addWidget(itemDisplay);
}
void MainWindow::clearView()
{
    MainDisplay *mainDisplay = findChild<MainDisplay *>(); // Find the main display 
    if (mainDisplay)
    {
        layout()->removeWidget(mainDisplay); // Remove the main display
        delete mainDisplay;                  // Delete the main display
    }
    ItemDisplay *itemDisplay = findChild<ItemDisplay *>(); // Find the item display
    if (itemDisplay)
    {
        layout()->removeWidget(itemDisplay); // Remove the item display
        delete itemDisplay;                  // Delete the item display
    }
    QWidget *widget = findChild<QWidget *>("newItemWidget"); // Find the widget by object name
    if (widget)
    {
        layout()->removeWidget(widget); // Remove the widget
        delete widget;                  // Delete the widget
    }
}

void MainWindow::createHeader()
{
    QWidget *widget = new QWidget(this);
    widget->setObjectName("newItemWidget");
    QHBoxLayout *widgetLayout = new QHBoxLayout(widget);
    
    
    SearchBar *searchBar = new SearchBar(widget);
    widgetLayout->addWidget(searchBar);
    connect(searchBar, &SearchBar::queryChanged, this, &MainWindow::search); // Connect search signal to mainDisplay search to filter the items


    QPushButton *newItemButton = new QPushButton("Create new Item", widget);
    QMenu *newItemMenu = new QMenu(newItemButton);
    QAction *newArticle = new QAction("Article", newItemMenu);
    QAction *newBook = new QAction("Book", newItemMenu);
    QAction *newFilm = new QAction("Film", newItemMenu);
    QAction *newMusic = new QAction("Music", newItemMenu);
    QAction *newPodcast = new QAction("Podcast", newItemMenu);

    newItemMenu->addAction(newArticle);
    newItemMenu->addAction(newBook);
    newItemMenu->addAction(newFilm);
    newItemMenu->addAction(newMusic);
    newItemMenu->addAction(newPodcast);
    newItemButton->setMenu(newItemMenu);

    connect(newArticle, &QAction::triggered, this, &MainWindow::onNewItemButtonClicked);
    connect(newBook, &QAction::triggered, this, &MainWindow::onNewItemButtonClicked);
    connect(newFilm, &QAction::triggered, this, &MainWindow::onNewItemButtonClicked);
    connect(newMusic, &QAction::triggered, this, &MainWindow::onNewItemButtonClicked);
    connect(newPodcast, &QAction::triggered, this, &MainWindow::onNewItemButtonClicked);

    widgetLayout->addWidget(newItemButton);


    layout()->addWidget(widget);
}
