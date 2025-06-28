#include <SearchBar.h>
#include <qboxlayout.h>
#include <QTimer>

SearchBar::SearchBar(QWidget *parent) : QWidget(parent), searchTimer(new QTimer(this))
{
    searchTimer->setInterval(300); // Delay da quando l'utente smette di digitare
    searchTimer->setSingleShot(true); // Emette l'evento searchTimer solo una volta dopo il timeout

    // Initialize the search text edit
    searchTextEdit = new QLineEdit(this);

    connect(searchTextEdit, &QLineEdit::textChanged, this, [this]() {
        searchTimer->start(); //Ogni volta che l'utente digita, riavvia il timer
    });
    connect(searchTimer, &QTimer::timeout, this, [this]() {
        emit queryChanged(searchTextEdit->text());
    });

    searchTextEdit->setPlaceholderText("Search...");
    searchTextEdit->setFixedHeight(30);

    setLayout(new QHBoxLayout(this));
    layout()->addWidget(searchTextEdit);
}