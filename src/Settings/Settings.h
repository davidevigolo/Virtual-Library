#pragma once
#include <QMap>
#include <string>
#include <QString>
#include <QColor>

enum Theme{
    DARK,
    LIGHT,
    CUSTOM
};

typedef struct{
    public:
        Theme selectedTheme;
        QMap<QString,QColor> customPaletteData;
        QMap<QString,int> weights;
} SettingsData;

class Settings{
    private:
        static SettingsData settings;
    public:
        Settings();
        static void setSettings(SettingsData newSettings);
        static SettingsData getSettings();
        static void saveSettings();
        static QString themeToText(int);
        static Theme textToTheme(QString);
};