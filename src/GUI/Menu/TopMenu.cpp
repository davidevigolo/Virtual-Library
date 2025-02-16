#include <TopMenu.h>

TopMenu::TopMenu(QWidget *parent) : QMenuBar(parent)
{
    QMenu *fileMenu = addMenu(tr("&File"));
    QAction *exitAction = new QAction(tr("&Exit"), this);
    fileMenu->addAction(exitAction);
    connect(exitAction, &QAction::triggered, this, [this]() {
        QApplication::quit();
    });
}