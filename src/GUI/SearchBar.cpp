#include <SearchBar.h>
#include <qboxlayout.h>

SearchBar::SearchBar(QWidget *parent) : QWidget(parent)
{
    searchButton = new QPushButton("Search", this);
    searchTextEdit = new QLineEdit(this);
    searchTextEdit->setPlaceholderText("Search...");
    searchTextEdit->setFixedHeight(30);
    searchButton->setFixedHeight(30);
    searchButton->setFixedWidth(100);
    searchButton->setStyleSheet("background-color: white;");
    searchTextEdit->setStyleSheet("background-color: white;");
    searchButton->setStyleSheet("background-color: white;");
    QHBoxLayout *searchLayout = new QHBoxLayout(this);
    searchLayout->addWidget(searchTextEdit);
    searchLayout->addWidget(searchButton);
    setLayout(searchLayout);
}

QString SearchBar::getSearchText()
{
    return searchTextEdit->text();
}

void SearchBar::setSearchText(QString text)
{
    searchTextEdit->setText(text);
}