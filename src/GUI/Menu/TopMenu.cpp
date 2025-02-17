#include <TopMenu.h>

TopMenu::TopMenu(QWidget *parent) : QMenuBar(parent)
{
    QMenu *fileMenu = addMenu(tr("&File"));
    exitAction = new QAction(tr("&Exit"), this);
    newFile = new QAction(tr("Open new file"), this);
    saveAs = new QAction(tr("Save as"),this);
    fileMenu->addAction(exitAction);
    fileMenu->addAction(newFile);
    fileMenu->addAction(saveAs);
}