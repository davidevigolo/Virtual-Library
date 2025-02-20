#pragma once
#include <map>
#include <string>

typedef struct{
    public:
        bool darkMode;
        std::map<std::string,int> weights;
} SettingsData;

class Settings{
    private:
        static SettingsData settings;
    public:
        Settings();
        static void setSettings(SettingsData newSettings);
};