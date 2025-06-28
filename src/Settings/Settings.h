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

class SettingsData {
    private:
        static SettingsData* instance;
        Theme selectedTheme;
        QMap<QString,QColor> customPaletteData;
        QMap<QString,int> weights;
        
        // Private constructor to prevent instantiation
        SettingsData() = default;

    public:
        // Delete copy constructor and assignment operator
        SettingsData(const SettingsData&) = delete;
        SettingsData& operator=(const SettingsData&) = delete;

        static SettingsData* getInstance();

        // Getters and setters
        Theme getSelectedTheme() const { return selectedTheme; }
        void setSelectedTheme(Theme theme) { selectedTheme = theme; }
        
        QMap<QString,QColor>& getCustomPaletteData() { return customPaletteData; }
        void setCustomPaletteData(const QMap<QString,QColor>& palette) { customPaletteData = palette; }
        
        QMap<QString,int>& getWeights() { return weights; }
        void setWeights(const QMap<QString,int>& w) { weights = w; }

        void setDefaultSettings();
};

class Settings {
    public:
        Settings();
        static QString themeToText(int);
        static Theme textToTheme(QString);
        static void setAppPalette(QMap<QString,QColor>& customPaletteData = SettingsData::getInstance()->getCustomPaletteData(),
                                    Theme selectedTheme = SettingsData::getInstance()->getSelectedTheme());
        static void saveSettings();
};