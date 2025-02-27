#include "Settings.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QPalette>
#include <QApplication>

SettingsData* SettingsData::instance = nullptr;

SettingsData* SettingsData::getInstance() {
    if (instance == nullptr) {
        instance = new SettingsData();
    }
    return instance;
}


void SettingsData::setDefaultSettings() {
    SettingsData* settings = SettingsData::getInstance();
    settings->setSelectedTheme(Theme::DARK);
    settings->setWeights({
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
    });
    settings->setCustomPaletteData({
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
    });
}

Settings::Settings() {
    QFile file("settings.json");
    SettingsData::getInstance()->setDefaultSettings();
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open settings.json file.");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject jsonObj = doc.object();

    SettingsData* settings = SettingsData::getInstance();
    settings->setSelectedTheme(static_cast<Theme>(jsonObj["selectedTheme"].toInt()));

    QJsonObject weightsObj = jsonObj["modifiedValues"].toObject();
    for (const QString& key : weightsObj.keys()) {
        settings->getWeights()[key] = weightsObj[key].toInt();
    }

    QJsonObject customPaletteDataObj = jsonObj["customPaletteData"].toObject();
    for (const QString& key : customPaletteDataObj.keys()) {
        settings->getCustomPaletteData()[key] = QColor(customPaletteDataObj[key].toString());
    }
}


void Settings::saveSettings() {
    SettingsData* settings = SettingsData::getInstance();
    QFile file("settings.json");
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject _settings;
        
        QJsonObject modifiedValues;
        for (auto key : settings->getWeights().keys()) {
            modifiedValues[key] = settings->getWeights().value(key);
        }
        _settings["modifiedValues"] = modifiedValues;

        QJsonObject modifiedCustomPaletteData;
        for (auto key : settings->getCustomPaletteData().keys()) {
            modifiedCustomPaletteData[key] = settings->getCustomPaletteData().value(key).name(QColor::HexArgb);
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
    if (selectedTheme == Theme::DARK) {
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
    } else if (selectedTheme == Theme::LIGHT) {
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
    } else {
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

QString Settings::themeToText(int theme) {
    switch (theme) {
    case Theme::DARK:
        return "Dark";
    case Theme::LIGHT:
        return "Light";
    case Theme::CUSTOM:
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
