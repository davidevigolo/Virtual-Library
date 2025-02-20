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

    settings.darkMode = jsonObj["darkMode"].toBool();

    QJsonObject weightsObj = jsonObj["modifiedValues"].toObject();
    for (const QString& key : weightsObj.keys()) {
        qDebug() << key << ": " << weightsObj[key].toInt();
        settings.weights[key.toStdString()] = weightsObj[key].toInt();
    }
    setSettings(settings);
}

void Settings::setSettings(SettingsData newSettings) {
    settings = newSettings;
}

SettingsData Settings::getSettings() {
    return settings;
}