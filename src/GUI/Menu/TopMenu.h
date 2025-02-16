#include <qmenu.h>
#include <qmenubar.h>
#include <qaction.h>
#include <qapplication.h>

class TopMenu : public QMenuBar {
    Q_OBJECT
public:
    TopMenu(QWidget *parent = 0);
    ~TopMenu() = default;
};
    