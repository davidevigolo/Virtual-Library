#include <SearchBar.h>
#include <qboxlayout.h>

SearchBar::SearchBar(QWidget *parent) : QWidget(parent)
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
    emit queryChanged(searchTextEdit->text());
}