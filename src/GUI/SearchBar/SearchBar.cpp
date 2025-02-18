#include <SearchBar.h>
#include <qboxlayout.h>

SearchBar::SearchBar(QWidget *parent) : QWidget(parent)
{
    searchTextEdit = new QLineEdit(this);

    connect(searchTextEdit, &QLineEdit::textChanged, this, &SearchBar::searchEvent);

    searchTextEdit->setPlaceholderText("Search...");
    searchTextEdit->setFixedHeight(30);

    searchTextEdit->setStyleSheet("background-color: white; color: black;");
    QHBoxLayout *searchLayout = new QHBoxLayout(this);
    searchLayout->addWidget(searchTextEdit);
    setLayout(searchLayout);
}

void SearchBar::searchEvent()
{
    emit queryChanged(searchTextEdit->text());
}