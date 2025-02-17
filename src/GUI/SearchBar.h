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
    QString getSearchText();
    void setSearchText(QString text);
    void setSearchButtonAction(std::function<void()> action);
};