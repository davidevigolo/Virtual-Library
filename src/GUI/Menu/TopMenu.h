#include <qmenu.h>
#include <qmenubar.h>
#include <qaction.h>
#include <qapplication.h>

class TopMenu : public QMenuBar {
    Q_OBJECT
    QAction* exitAction;
    QAction* newFile;
    QAction* saveAs;
public:
    TopMenu(QWidget *parent = 0);
    ~TopMenu() = default;
    // Getters
    QAction* getExitAction() const {
        return exitAction;
    }

    QAction* getNewFileAction() const {
        return newFile;
    }

    QAction* getSaveAsAction() const {
        return saveAs;
    }
};;
    