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
#include <qmessagebox.h>
#include <SettingsDisplay.h>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), fileManager(nullptr), searchEngine()
{
    setAppStyleSheet();
    TopMenu *menuBar = new TopMenu(this);

    QLabel *welcomeText = new QLabel("<html><body><p><strong>Welcome to Virtual Library!</strong></p>"
                                     "<p>This application allows you to manage your media items, such as articles, books, films, music, and podcasts.</p>"
                                     "<p>You can create new items, search for existing items, and perform various file actions.</p>"
                                     "<p>Use the top menu to create new files, save the current file, or save the file with a different name.</p>"
                                     "<p>The search bar allows you to search for specific items based on a query.</p>"
                                     "<p>To create a new item, click on the 'Create new Item' button and select the item type from the dropdown menu.</p>"
                                     "<p>Once an item is created, you can view and edit its details in the item display.</p>"
                                     "<p>To delete an item, click on the 'Delete' button in the item display.</p>"
                                     "<p>Enjoy using Virtual Library!</p>"
                                     "<p>Source code available <a href=\"https://github.com/davidevigolo/Virtual-Library\">here</a></p>"
                                     "</body></html>");
    welcomeText->setOpenExternalLinks(true);//to make the link clickable
    welcomeText->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    welcomeText->setObjectName("welcomeText");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QObject::connect(menuBar, &TopMenu::NewFileSignal, this, &MainWindow::loadFromFile);
    QObject::connect(menuBar, &TopMenu::SaveSignal, this, &MainWindow::save);
    QObject::connect(menuBar, &TopMenu::SaveAsSignal, this, &MainWindow::saveToFile);
    QObject::connect(menuBar, &TopMenu::SettingsSignal, this, &MainWindow::onSettingsSignal);

    mainLayout->setMenuBar(menuBar);

    // Connect itemsLoaded signal to  mainDisplay setAreas to update the view

    createHeader();
    mainLayout->addWidget(welcomeText);

    setLayout(mainLayout);

    setWindowTitle("Virtual Library");
}

void MainWindow::loadFromFile()
{
    clearView();
    createHeader();
    addMainDisplay();
    QString filePath = QFileDialog::getOpenFileName(this, "Select File", "", "Files (*.xml *.json);;All Files (*)");
    if (!filePath.isEmpty())
    {
        fileManager = ManagerFactory(filePath).create();
        if (!fileManager)
        {
            QMessageBox *notSupported = new QMessageBox(this);
            notSupported->setText("File computation gone wrong");
            notSupported->setStandardButtons(QMessageBox::Ok);
        }
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
    if (filteredItems.size() == 0)
    {
        emit noResults(query);
        return;
    }
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
    addMainDisplay();
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
    auto welcomeText = findChild<QLabel *>("welcomeText");
    welcomeText->hide();
}

void MainWindow::createHeader()
{
    QWidget *widget = new QWidget(this);
    widget->setObjectName("newItemWidget");
    QHBoxLayout *widgetLayout = new QHBoxLayout(widget);

    SearchBar *searchBar = new SearchBar(widget);
    searchBar->setObjectName("searchBar");
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

void MainWindow::addMainDisplay()
{
    MainDisplay *mainDisplay = new MainDisplay(this);
    mainDisplay->setObjectName("mainDisplay");
    connect(this, &MainWindow::noResults, mainDisplay, &MainDisplay::onNoResults);
    connect(mainDisplay, &MainDisplay::itemButtonClicked, this, &MainWindow::onButtonClicked);
    connect(this, &MainWindow::itemsLoaded, mainDisplay, &MainDisplay::setAreas);
    layout()->addWidget(mainDisplay);
}

void MainWindow::onSettingsSignal()
{
    SettingsDisplay *settingsDisplay = new SettingsDisplay;
    connect(settingsDisplay, &SettingsDisplay::settingsChanged, this, &MainWindow::onSettingsChanged);
    connect(settingsDisplay, &SettingsDisplay::settingsDisplayClosed, this, &MainWindow::onSettingsClosed);
    settingsDisplay->setAttribute(Qt::WA_DeleteOnClose);
    settingsDisplay->show();
    settingsDisplay->resize(400, 400);
}

void MainWindow::onSettingsChanged()
{
    setAppStyleSheet();
}

void MainWindow::setAppStyleSheet()
{
    QPalette palette = this->palette();
    if (Settings::getSettings().selectedTheme == 0) //DARK
    {
        palette.setColor(QPalette::Window, QColor(30, 30, 30));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, QColor(50, 50, 50));
        palette.setColor(QPalette::AlternateBase, QColor(50, 50, 50));
        palette.setColor(QPalette::ToolTipBase, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, QColor(50, 50, 50));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::BrightText, Qt::red);
        palette.setColor(QPalette::Link, QColor(42, 130, 218));
        palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        palette.setColor(QPalette::HighlightedText, Qt::black);
    }
    else if (Settings::getSettings().selectedTheme == 1) //LIGHT
    {
        palette.setColor(QPalette::Window, Qt::white);
        palette.setColor(QPalette::WindowText, Qt::black);
        palette.setColor(QPalette::Base, Qt::white);
        palette.setColor(QPalette::AlternateBase, Qt::white);
        palette.setColor(QPalette::ToolTipBase, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::black);
        palette.setColor(QPalette::Text, Qt::black);
        palette.setColor(QPalette::Button, Qt::white);
        palette.setColor(QPalette::ButtonText, Qt::black);
        palette.setColor(QPalette::BrightText, Qt::red);
        palette.setColor(QPalette::Link, QColor(42, 130, 218));
        palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        palette.setColor(QPalette::HighlightedText, Qt::white);
    }
    else 
    {
        // Set palette based on settings value
        auto settings = Settings::getSettings().customPaletteData;
        for (const auto& key : settings.keys()) {
            qDebug() << key << ": " << settings[key];
        }
        palette.setColor(QPalette::Window, settings["Window"]);
        palette.setColor(QPalette::WindowText, settings["WindowText"]);
        palette.setColor(QPalette::Base, settings["Base"]);
        palette.setColor(QPalette::AlternateBase, settings["AlternateBase"]);
        palette.setColor(QPalette::ToolTipBase, settings["ToolTipBase"]);
        palette.setColor(QPalette::ToolTipText, settings["ToolTipText"]);
        palette.setColor(QPalette::Text, settings["Text"]);
        palette.setColor(QPalette::Button, settings["Button"]);
        palette.setColor(QPalette::ButtonText, settings["ButtonText"]);
        palette.setColor(QPalette::BrightText, settings["BrightText"]);
        palette.setColor(QPalette::Link, settings["Link"]);
        palette.setColor(QPalette::Highlight, settings["Highlight"]);
        palette.setColor(QPalette::HighlightedText, settings["HighlightedText"]);
    }
    qApp->setPalette(palette);
}

void MainWindow::onSettingsClosed()
{
    setAppStyleSheet();
}