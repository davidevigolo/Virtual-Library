#pragma once
#include <qmenu.h>
#include <qmenubar.h>
#include <qaction.h>
#include <qapplication.h>

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
    