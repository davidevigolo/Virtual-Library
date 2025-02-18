#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class SearchBar : public QWidget
{
    Q_OBJECT
private:
    QLineEdit *searchTextEdit;
    QPushButton *searchButton;
public:
    SearchBar(QWidget *parent = nullptr);
private slots:
    void searchEvent();
signals:
    void queryChanged(QString query);
};