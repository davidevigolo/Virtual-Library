#pragma once
#include <QMap>
#include <string>
#include <QString>
#include <QColor>


/**
    * @brief Enum to represent the different themes that the application can have
    *
*/
enum Theme{
    DARK,
    LIGHT,
    CUSTOM
};

/**
    * @brief Struct to represent the settings of the application
    *
    * @param selectedTheme The selected theme of the application
    * @param customPaletteData The custom palette data of the application
    * @param weights The weights of the search engine of the application
*/

typedef struct{
    public:
        Theme selectedTheme;
        QMap<QString,QColor> customPaletteData;
        QMap<QString,int> weights;
} SettingsData;

/**
 * @brief Class to manage the settings of the application
 * 
* @param settings The settings of the application
* @param setDefaultSettings Function to set the default settings of the application

*/

class Settings{
    private:
        static SettingsData settings;
        static void setDefaultSettings();
    public:
        Settings();
        static void setSettings(SettingsData newSettings);
        static SettingsData getSettings();
        static void saveSettings();
        static QString themeToText(int);
        static Theme textToTheme(QString);
        static void setAppPalette(QMap<QString,QColor>& customPaletteData,Theme selectedTheme);
};