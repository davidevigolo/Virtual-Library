#pragma once
#include <QWidget>
#include <map>
#include <string>
#include <Settings.h>

/**
    *A class that represents the settings display
    *It allows the user to change the theme of the application
    *It allows the user to change the weight of the search algorithm of the application
*/

class SettingsDisplay : public QWidget{
    Q_OBJECT
private:
    Theme selectedTheme;
    QMap<QString,QColor> customPaletteData;
    QMap<QString,int> weights;
    void closeEvent(QCloseEvent *event) override;
    void setAppPalette();
public:
    SettingsDisplay(QWidget* parent = nullptr);
private slots:
    void onApply();
    void onReset();
    void onChangeColor();
    void onChangeTheme();
};