#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
};