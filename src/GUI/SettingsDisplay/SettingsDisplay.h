#pragma once
#include <QWidget>
#include <map>
#include <string>
#include <Settings.h>

class SettingsDisplay : public QWidget{
    Q_OBJECT
private:
    bool darkMode;
    std::map<std::string,int> weights;
public:
    SettingsDisplay(QWidget* parent = nullptr, const bool &dark = true);
signals:
    void settingsDisplayClosed();
private slots:
    void onThemeChanged();
    void onGoBack();
    void onApply();
};