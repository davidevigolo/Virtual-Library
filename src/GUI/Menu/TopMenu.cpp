#include <TopMenu.h>

TopMenu::TopMenu(QWidget *parent) : QMenuBar(parent)
{
    QMenu *fileMenu = addMenu(tr("&File"));
    exitAction = new QAction(tr("&Exit"), this);
    newFile = new QAction(tr("Open new file"), this);
    save = new QAction(tr("Save"),this);
    saveAs = new QAction(tr("Save as"),this);
    fileMenu->addAction(exitAction);
    fileMenu->addAction(newFile);
    fileMenu->addAction(save);
    fileMenu->addAction(saveAs);
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(newFile, &QAction::triggered, this, &TopMenu::NewFile);
    connect(save, &QAction::triggered, this, &TopMenu::Save);
    connect(saveAs, &QAction::triggered, this, &TopMenu::SaveAs);
}

void TopMenu::NewFile()
{
    emit NewFileSignal();
}

void TopMenu::Save()
{
    emit SaveSignal();
}

void TopMenu::SaveAs()
{
    emit SaveAsSignal();
}