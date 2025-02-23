#pragma once
#include <qmenu.h>
#include <qmenubar.h>
#include <qaction.h>
#include <qapplication.h>

/**
 * @class TopMenu
 * @brief A custom menu bar for the application.
 *
 * The TopMenu class provides a menu bar with actions
 * for creating a new file, saving, saving as, and accessing settings.
 *
 * @section Actions
 * - QAction* exitAction: Action to exit the application.
 * - QAction* newFile: Action to create a new file.
 * - QAction* save: Action to save the current file.
 * - QAction* saveAs: Action to save the current file with a new name.
 * - QAction* settings: Action to open the settings dialog.
 *
 * @section Slots
 * - used to handle the actions of the menu and emit signals
 *
 * @section Signals
 * - void NewFileSignal(): Signal emitted when a new file is created.
 * - void SaveSignal(): Signal emitted when the current file is saved.
 * - void SaveAsSignal(): Signal emitted when the current file is saved with a new name.
 * - void SettingsSignal(): Signal emitted when the settings dialog is opened.
*/
class TopMenu : public QMenuBar {
    Q_OBJECT
    QAction* exitAction;
    QAction* newFile;
    QAction* save;
    QAction* saveAs;
    QAction* settings;
public:
    TopMenu(QWidget *parent = 0);
    ~TopMenu() = default;
    // Getters
private slots:
    void NewFile();
    void Save();
    void SaveAs();
    void Settings();
signals:
    void NewFileSignal();
    void SaveSignal();
    void SaveAsSignal();
    void SettingsSignal();
};
    