#include <Settings.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

SettingsData Settings::settings;

Settings::Settings() {
    QFile file("settings.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open settings.json file.");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject jsonObj = doc.object();

    settings.selectedTheme = static_cast<Theme>(jsonObj["selectedTheme"].toInt());

    QJsonObject weightsObj = jsonObj["modifiedValues"].toObject();
    for (const QString& key : weightsObj.keys()) {
        settings.weights[key] = weightsObj[key].toInt();
    }

    QJsonObject customPaletteDataObj = jsonObj["customPaletteData"].toObject();
    for (const QString& key : customPaletteDataObj.keys()) {
        settings.customPaletteData[key] = QColor(customPaletteDataObj[key].toString());
    }
    setSettings(settings);
}

void Settings::setSettings(SettingsData newSettings) {
    settings = newSettings;
}

SettingsData Settings::getSettings() {
    return settings;
}

void Settings::saveSettings() {
        //save the weight change in a file
    QFile file("settings.json");
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject _settings;
        
        QJsonObject modifiedValues;

        for(auto key : settings.weights.keys()) {
            modifiedValues[key] = settings.weights.value(key);
        }
        
        _settings["modifiedValues"] = modifiedValues;

        QJsonObject modifiedCustomPaletteData;

        for(auto key : settings.customPaletteData.keys()) {
            modifiedCustomPaletteData[key] = settings.customPaletteData.value(key).name(QColor::HexArgb);
        }

        _settings["customPaletteData"] = modifiedCustomPaletteData;
        
        QJsonDocument doc(_settings);
        file.write(doc.toJson());
        file.close();
    } else {
        qWarning("Could not open Settings.json to apply the changes");
    }   
}

QString Settings::themeToText(int theme) {
    switch (theme) {
    case 0:
        return "Dark";
    case 1:
        return "Light";
    case 2:
        return "Custom";
    default:
        return "Unknown";
    }
}

Theme Settings::textToTheme(QString theme) {
    if (theme == "Dark") {
        return Theme::DARK;
    } else if (theme == "Light") {
        return Theme::LIGHT;
    } else if (theme == "Custom") {
        return Theme::CUSTOM;
    } else {
        return Theme::DARK;
    }
}