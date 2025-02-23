#include <Settings.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QPalette>
#include <qapplication.h>

SettingsData Settings::settings;

Settings::Settings() {
    QFile file("settings.json");
    setDefaultSettings();
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

void Settings::setAppPalette(QMap<QString,QColor>& customPaletteData, Theme selectedTheme) {
    QPalette* palette = new QPalette();
    if (selectedTheme == 0) // DARK
    {
        palette->setColor(QPalette::Window, QColor(30, 30, 30));
        palette->setColor(QPalette::WindowText, Qt::white);
        palette->setColor(QPalette::Base, QColor(50, 50, 50));
        palette->setColor(QPalette::AlternateBase, QColor(50, 50, 50));
        palette->setColor(QPalette::ToolTipBase, Qt::white);
        palette->setColor(QPalette::ToolTipText, Qt::white);
        palette->setColor(QPalette::Text, Qt::white);
        palette->setColor(QPalette::Button, QColor(50, 50, 50));
        palette->setColor(QPalette::ButtonText, Qt::white);
        palette->setColor(QPalette::BrightText, Qt::red);
        palette->setColor(QPalette::Link, QColor(42, 130, 218));
        palette->setColor(QPalette::Highlight, QColor(42, 130, 218));
        palette->setColor(QPalette::HighlightedText, Qt::black);
    }
    else if (selectedTheme == 1) // LIGHT
    {
        palette->setColor(QPalette::Window, Qt::white);
        palette->setColor(QPalette::WindowText, Qt::black);
        palette->setColor(QPalette::Base, Qt::white);
        palette->setColor(QPalette::AlternateBase, Qt::white);
        palette->setColor(QPalette::ToolTipBase, Qt::white);
        palette->setColor(QPalette::ToolTipText, Qt::black);
        palette->setColor(QPalette::Text, Qt::black);
        palette->setColor(QPalette::Button, Qt::white);
        palette->setColor(QPalette::ButtonText, Qt::black);
        palette->setColor(QPalette::BrightText, Qt::red);
        palette->setColor(QPalette::Link, QColor(42, 130, 218));
        palette->setColor(QPalette::Highlight, QColor(42, 130, 218));
        palette->setColor(QPalette::HighlightedText, Qt::white);
    }
    else
    {
        // Set palette based on settings value
        palette->setColor(QPalette::Window, customPaletteData["Window"]);
        palette->setColor(QPalette::WindowText, customPaletteData["WindowText"]);
        palette->setColor(QPalette::Base, customPaletteData["Base"]);
        palette->setColor(QPalette::AlternateBase, customPaletteData["AlternateBase"]);
        palette->setColor(QPalette::ToolTipBase, customPaletteData["ToolTipBase"]);
        palette->setColor(QPalette::ToolTipText, customPaletteData["ToolTipText"]);
        palette->setColor(QPalette::Text, customPaletteData["Text"]);
        palette->setColor(QPalette::Button, customPaletteData["Button"]);
        palette->setColor(QPalette::ButtonText, customPaletteData["ButtonText"]);
        palette->setColor(QPalette::BrightText, customPaletteData["BrightText"]);
        palette->setColor(QPalette::Link, customPaletteData["Link"]);
        palette->setColor(QPalette::Highlight, customPaletteData["Highlight"]);
        palette->setColor(QPalette::HighlightedText, customPaletteData["HighlightedText"]);
    }
    qApp->setPalette(*palette);
}

void Settings::setDefaultSettings(){
    settings.selectedTheme = Theme::DARK;
    settings.weights = {
        {"Title", 10},
        {"Author", 5},
        {"Release Date", 5},
        {"Production House", 5},
        {"Genre", 5},
        {"Tags", 5},
        {"Format", 5},
        {"Language", 5},
        {"Edition", 5},
        {"Publisher", 5},
        {"ISBN", 5},
        {"Duration", 5},
        {"Director", 5},
        {"Tecnique", 5},
        {"Album", 5},
        {"Episode", 5}
    };
    settings.customPaletteData = {
        {"Window", QColor(30, 30, 30)},
        {"WindowText", Qt::white},
        {"Base", QColor(50, 50, 50)},
        {"AlternateBase", QColor(50, 50, 50)},
        {"ToolTipBase", Qt::white},
        {"ToolTipText", Qt::white},
        {"Text", Qt::white},
        {"Button", QColor(50, 50, 50)},
        {"ButtonText", Qt::white},
        {"BrightText", Qt::red},
        {"Link", QColor(42, 130, 218)},
        {"Highlight", QColor(42, 130, 218)},
        {"HighlightedText", Qt::black}
    };
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