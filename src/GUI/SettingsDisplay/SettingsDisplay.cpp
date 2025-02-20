#include <SettingsDisplay.h>
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>

SettingsDisplay::SettingsDisplay(QWidget* parent, const bool& dark): QWidget(parent), darkMode(dark) {
    this->setWindowTitle("Settings");
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    QPushButton *theme = new QPushButton("Mode", this);
    theme->setObjectName("theme");
    darkMode = false;
    onThemeChanged();
    connect(theme, &QPushButton::clicked, this, &SettingsDisplay::onThemeChanged);
    layout->addWidget(theme);

    QPushButton *Back = new QPushButton("Back", this);
    connect(Back, &QPushButton::clicked, this, &SettingsDisplay::onGoBack);
    layout->addWidget(Back);

    QPushButton* apply = new QPushButton("Apply", this);
    connect(apply, &QPushButton::clicked, this, &SettingsDisplay::onApply);
    layout->addWidget(apply);

    QVBoxLayout* weightsLayout = new QVBoxLayout();

    QStringList labels = {"Title", "Author", "Release Date", "Production House", "Genre", "Tags", "Format", "Language", "Edition", "Publisher", "ISBN", "Duration", "Director", "Tecnique", "Album", "Episode"};
    for (const QString& label : labels) {
        QHBoxLayout* rowLayout = new QHBoxLayout();
        QLabel* lbl = new QLabel(label, this);
        QSpinBox* spinBox = new QSpinBox(this);
        spinBox->setRange(0, 100);
        spinBox->setValue(weights[label.toStdString()]);
        connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), [this, label](int value) {
            weights[label.toStdString()] = value;
        });
        rowLayout->addWidget(lbl);
        rowLayout->addWidget(spinBox);
        weightsLayout->addLayout(rowLayout);
    }

    layout->addLayout(weightsLayout);


    setLayout(layout);



}

void SettingsDisplay::onThemeChanged() {
    auto theme = findChild<QPushButton*>("theme");
    if (!darkMode) {
        theme->setText("Dark Mode");
        theme->setStyleSheet("background-color: black; color: white;");
    } else {
        theme->setText("Light Mode");
        theme->setStyleSheet("background-color: white; color: black;");
    }
    darkMode = !darkMode;
}

void SettingsDisplay::onGoBack() {
    emit settingsDisplayClosed();
}

void SettingsDisplay::onApply() {
    //save the weight change in a file
    QFile file("settings.json");
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject settings;
        settings["darkMode"] = darkMode;
        
        QJsonObject modifiedValues;

        modifiedValues["Title"] = weights["Title"];
        modifiedValues["Author"] = weights["Author"];
        modifiedValues["Release Date"] = weights["Release Date"];
        modifiedValues["Production House"] = weights["Production House"];
        modifiedValues["Genre"] = weights["Genre"];
        modifiedValues["Tags"] = weights["Tags"];
        modifiedValues["Format"] = weights["Format"];
        modifiedValues["Language"] = weights["Language"];
        modifiedValues["Edition"] = weights["Edition"];
        modifiedValues["Publisher"] = weights["Publisher"];
        modifiedValues["ISBN"] = weights["ISBN"];
        modifiedValues["Duration"] = weights["Duration"];
        modifiedValues["Director"] = weights["Director"];
        modifiedValues["Tecnique"] = weights["Tecnique"];
        modifiedValues["Album"] = weights["Album"];
        modifiedValues["Episode"] = weights["Episode"];

        QJsonObject defaultValues;

        defaultValues["Title"] = 10;
        defaultValues["Author"] = 5;
        defaultValues["Release Date"] = 5;
        defaultValues["Production House"] = 5;
        defaultValues["Genre"] = 5;
        defaultValues["Tags"] = 5;
        defaultValues["Format"] = 5;
        defaultValues["Language"] = 5;
        defaultValues["Edition"] = 5;
        defaultValues["Publisher"] = 5;
        defaultValues["ISBN"] = 5;
        defaultValues["Duration"] = 5;
        defaultValues["Director"] = 5;
        defaultValues["Tecnique"] = 5;
        defaultValues["Album"] = 5;
        defaultValues["Episode"] = 5;
        
        settings["modifiedValues"] = modifiedValues;
        settings["defaultValues"] = defaultValues;

        QJsonDocument doc(settings);
        file.write(doc.toJson());
        file.close();
    } else {
        qWarning("Could not open Settings.json to apply the changes");
    }

    SettingsData settingsData;
    settingsData.darkMode = darkMode;
    settingsData.weights = weights;
    Settings::setSettings(settingsData);

    emit settingsDisplayClosed();

}
