#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

/** 
 * @class SearchBar
 * @brief A custom widget that provides a search bar with a text input.
 *
 * The SearchBar class provides a simple interface for
 * entering search queries and triggering search events. It contains a QLineEdit
 * for text input and a QPushButton to initiate the search.
 *
 * @signals
 *   - void queryChanged(QString query): Emitted when the search query changes.
 */


class SearchBar : public QWidget
{
    Q_OBJECT
private:
    QLineEdit *searchTextEdit;
    QPushButton *searchButton;
    QTimer *searchTimer;
public:
    SearchBar(QWidget *parent = nullptr);
signals:
    void queryChanged(QString query);
};