#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QIcon>
#include <QResizeEvent>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLabel>

class CustomScrollArea : public QScrollArea {
public:
    CustomScrollArea(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
};
