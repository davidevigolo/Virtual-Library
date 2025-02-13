#include <MainWindow.h>


MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu("File", menuBar);
    QAction *exitAction = new QAction("Exit", fileMenu);
    fileMenu->addAction(exitAction);
    QAction *newAction = new QAction("New", fileMenu);
    fileMenu->addAction(newAction);
    menuBar->addMenu(fileMenu);

    QObject::connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);

    QVBoxLayout *layout = new QVBoxLayout(this);
    for (int i = 0; i < 5; ++i) {
        QLabel *titleLabel = new QLabel(QString("Scroll Area %1").arg(i + 1));
        titleLabel->setAlignment(Qt::AlignLeft);
        layout->addWidget(titleLabel);

        ScrollPanel *scrollPanel = new ScrollPanel(i);

        CustomScrollArea *scrollArea = new CustomScrollArea;
        scrollArea->setWidget(scrollPanel);
        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        

        layout->addWidget(scrollArea);
    }

    
    mainLayout->addLayout(layout);
    setLayout(mainLayout);

    setWindowTitle("Test Application");
    setStyleSheet("background-color: gray;");
}