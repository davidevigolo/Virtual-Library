#include <SearchBar.h>
#include <qboxlayout.h>

SearchBar::SearchBar(QWidget *parent) : QWidget(parent)
{
    searchButton = new QPushButton("Search", this);
    searchTextEdit = new QLineEdit(this);

    connect(searchTextEdit, &QLineEdit::textChanged, this, &SearchBar::searchButtonClicked);
    connect(searchButton, &QPushButton::clicked, this, &SearchBar::searchButtonClicked);

    searchTextEdit->setPlaceholderText("Search...");
    searchTextEdit->setFixedHeight(30);
    searchButton->setFixedHeight(30);
    searchButton->setFixedWidth(100);
    searchButton->setStyleSheet("background-color: white; color: black;");
    searchTextEdit->setStyleSheet("background-color: white; color: black;");
    QHBoxLayout *searchLayout = new QHBoxLayout(this);
    searchLayout->addWidget(searchTextEdit);
    searchLayout->addWidget(searchButton);
    setLayout(searchLayout);
}

void SearchBar::searchButtonClicked()
{
    emit queryChanged(searchTextEdit->text());
}