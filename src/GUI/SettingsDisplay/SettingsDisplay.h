#pragma once
#include <QWidget>
#include <map>
#include <string>
#include <Settings.h>

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
signals:
    void settingsChanged();
private slots:
    void onApply();
    void onReset();
    void onChangeColor();
    void onChangeTheme();
};