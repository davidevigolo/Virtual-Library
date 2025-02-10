#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QPushButton *button = new QPushButton("Hello, World!", this);
    layout->addWidget(button);
    setLayout(layout);
    //ciao
}   