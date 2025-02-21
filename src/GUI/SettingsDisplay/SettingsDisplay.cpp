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
#include <qmessagebox.h>
#include <QColorDialog>
#include <qmenu.h>
#include <qlineedit.h>
#include <QComboBox>

SettingsDisplay::SettingsDisplay(QWidget* parent): QWidget(parent) {
    setObjectName("settingsDisplay");
    selectedTheme = Settings::getSettings().selectedTheme;
    customPaletteData = Settings::getSettings().customPaletteData;
    weights = Settings::getSettings().weights;

    this->setWindowTitle("Settings");
    
    auto settings = Settings::getSettings();
    QVBoxLayout *layout = new QVBoxLayout(this);
    QPushButton *theme = new QPushButton("Mode", this);
    theme->setObjectName("theme");
    layout->addWidget(theme);

    QPushButton* apply = new QPushButton("Apply", this);
    connect(apply, &QPushButton::clicked, this, &SettingsDisplay::onApply);
    layout->addWidget(apply);

    QComboBox* themeComboBox = new QComboBox(this);
    themeComboBox->addItem("Dark");
    themeComboBox->addItem("Light");
    themeComboBox->addItem("Custom");
    themeComboBox->setCurrentText(Settings::themeToText(selectedTheme));
    connect(themeComboBox, QOverload<const QString&>::of(&QComboBox::currentTextChanged), [this](const QString& theme) {
        selectedTheme = Settings::textToTheme(theme); // Convert QString to Theme
    });
    layout->addWidget(themeComboBox);

    QPushButton* reset = new QPushButton("Reset default weights", this);
    connect(reset, &QPushButton::clicked, this, &SettingsDisplay::onReset);
    layout->addWidget(reset);
    

    QHBoxLayout *containerLayout = new QHBoxLayout();
    QVBoxLayout *themeLayout = new QVBoxLayout();
    QVBoxLayout* weightsLayout = new QVBoxLayout();

    QStringList labels = {"Title", "Author", "Release Date", "Production House", "Genre", "Tags", "Format", "Language", "Edition", "Publisher", "ISBN", "Duration", "Director", "Tecnique", "Album", "Episode"};
    for (const QString& label : labels) {
        QHBoxLayout* rowLayout = new QHBoxLayout();
        QLabel* lbl = new QLabel(label, this);
        QSpinBox* spinBox = new QSpinBox(this);
        spinBox->setRange(0, 100);
        spinBox->setValue(settings.weights[label]);
        connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), [this, label](int value) {
            weights[label] = value;
        });
        rowLayout->addWidget(lbl);
        rowLayout->addWidget(spinBox);
        weightsLayout->addLayout(rowLayout);
    }

    QStringList paletteLabels = {"Window", "WindowText", "Base", "AlternateBase", "ToolTipBase", "ToolTipText", "Text", "Button", "ButtonText", "BrightText", "Link", "Highlight", "HighlightedText"};
    for (const QString& label : paletteLabels) {
        QHBoxLayout* rowLayout = new QHBoxLayout();
        QLabel* lbl = new QLabel(label, this);
        QColor color = settings.customPaletteData[label];
        QPushButton* colorPicker = new QPushButton(this);
        colorPicker->setObjectName(label);
        colorPicker->setStyleSheet("background-color: " + color.name() + ";");
        connect(colorPicker, &QPushButton::clicked, [this, label, colorPicker]() {
            QColor color = QColorDialog::getColor(customPaletteData[label], this, "Select Color");
            if (color.isValid()) {
                customPaletteData[label] = color;
                colorPicker->setStyleSheet("background-color: " + color.name() + ";");
            }
        });
        rowLayout->addWidget(lbl);
        rowLayout->addWidget(colorPicker);
        themeLayout->addLayout(rowLayout);
    }
    containerLayout->addLayout(weightsLayout);
    containerLayout->addLayout(themeLayout);
    layout->addLayout(containerLayout);


    setLayout(layout);



}

void SettingsDisplay::onGoBack() {
    emit settingsDisplayClosed();
}

void SettingsDisplay::onApply() {
    SettingsData settingsData;
    settingsData.selectedTheme = selectedTheme;
    settingsData.customPaletteData = customPaletteData;
    settingsData.weights = weights;
    Settings::setSettings(settingsData);
    Settings::saveSettings();

    emit settingsChanged();
    emit settingsDisplayClosed();

}

void SettingsDisplay::onReset(){
    QMessageBox* confirmReset = new QMessageBox(this);
    confirmReset->setWindowTitle("Reset");
    confirmReset->setText("Are you sure you want to reset the weights?");
    confirmReset->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    confirmReset->setDefaultButton(QMessageBox::No);
    for (auto it = weights.begin(); it != weights.end(); ++it) {
        it.value() = 5;
        if (it.key() == "Title") {
            it.value() = 10;
        }
    }
}