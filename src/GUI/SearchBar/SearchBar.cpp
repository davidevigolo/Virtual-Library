#include <SearchBar.h>
#include <qboxlayout.h>
#include <QTimer>

SearchBar::SearchBar(QWidget *parent) : QWidget(parent), searchLock(false)
{
    searchTextEdit = new QLineEdit(this);

    connect(searchTextEdit, &QLineEdit::textChanged, this, &SearchBar::searchEvent);

    searchTextEdit->setPlaceholderText("Search...");
    searchTextEdit->setFixedHeight(30);

    setLayout(new QHBoxLayout(this));
    layout()->addWidget(searchTextEdit);
}

void SearchBar::searchEvent()
{
    if(searchLock) return;
    searchLock = true;
    emit queryChanged(searchTextEdit->text());
    QTimer::singleShot(1000, this, [this](){
        searchLock = false;
        emit queryChanged(searchTextEdit->text());
    });
    // emit queryChanged(searchTextEdit->text());
}