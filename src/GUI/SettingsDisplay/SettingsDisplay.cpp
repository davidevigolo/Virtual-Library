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
#include <qapplication.h>

SettingsDisplay::SettingsDisplay(QWidget *parent) : QWidget(parent)
{
    setObjectName("settingsDisplay");
    selectedTheme = Settings::getSettings().selectedTheme;
    customPaletteData = Settings::getSettings().customPaletteData;
    weights = Settings::getSettings().weights;

    this->setWindowTitle("Settings");

    auto settings = Settings::getSettings();
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *apply = new QPushButton("Apply", this);
    connect(apply, &QPushButton::clicked, this, &SettingsDisplay::onApply);
    layout->addWidget(apply);

    QVBoxLayout *themeChangeLayout = new QVBoxLayout();
    QLabel *themeLabel = new QLabel("Theme", this);
    themeLabel->setAlignment(Qt::AlignCenter);
    themeChangeLayout->addWidget(themeLabel);
    QComboBox *themeComboBox = new QComboBox(this);
    themeComboBox->addItem("Dark");
    themeComboBox->addItem("Light");
    themeComboBox->addItem("Custom");
    themeComboBox->setObjectName("theme");
    themeComboBox->setCurrentText(Settings::themeToText(selectedTheme));
    connect(themeComboBox, &QComboBox::currentTextChanged, this, &SettingsDisplay::onChangeTheme);
    themeChangeLayout->addWidget(themeComboBox);
    layout->addLayout(themeChangeLayout);

    QPushButton *reset = new QPushButton("Reset default weights", this);
    connect(reset, &QPushButton::clicked, this, &SettingsDisplay::onReset);
    layout->addWidget(reset);

    QHBoxLayout *containerLayout = new QHBoxLayout();
    QVBoxLayout *themeLayout = new QVBoxLayout();
    QVBoxLayout *weightsLayout = new QVBoxLayout();

    QStringList labels = {"Title", "Author", "Release Date", "Production House", "Genre", "Tags", "Format", "Language", "Edition", "Publisher", "ISBN", "Duration", "Director", "Tecnique", "Album", "Episode"};
    for (const QString &label : labels)
    {
        QHBoxLayout *rowLayout = new QHBoxLayout();
        QLabel *lbl = new QLabel(label, this);
        QSpinBox *spinBox = new QSpinBox(this);
        spinBox->setRange(0, 100);
        spinBox->setObjectName(label); // to find it later
        spinBox->setValue(settings.weights[label]);
        connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), [this, label](int value)
                { weights[label] = value; });
        rowLayout->addWidget(lbl);
        rowLayout->addWidget(spinBox);
        weightsLayout->addLayout(rowLayout);
    }

    QStringList paletteLabels = {"Window", "WindowText", "Base", "AlternateBase", "ToolTipBase", "ToolTipText", "Text", "Button", "ButtonText", "BrightText", "Link", "Highlight", "HighlightedText"};

    for (const QString &label : paletteLabels)
    {
        QHBoxLayout *rowLayout = new QHBoxLayout();
        QLabel *lbl = new QLabel(label, this);
        QColor color = settings.customPaletteData[label];
        QPushButton *colorPicker = new QPushButton(this);
        colorPicker->setObjectName(label);
        colorPicker->setStyleSheet("background-color: " + color.name() + ";");
        connect(colorPicker, &QPushButton::clicked, this, &SettingsDisplay::onChangeColor);
        rowLayout->addWidget(lbl);
        rowLayout->addWidget(colorPicker);
        themeLayout->addLayout(rowLayout);
    }
    containerLayout->addLayout(weightsLayout);
    containerLayout->addLayout(themeLayout);
    layout->addLayout(containerLayout);

    setLayout(layout);
}

void SettingsDisplay::onApply()
{
    SettingsData settingsData;
    settingsData.selectedTheme = selectedTheme;
    settingsData.customPaletteData = customPaletteData;
    settingsData.weights = weights;
    Settings::setSettings(settingsData);
    Settings::saveSettings();
}

void SettingsDisplay::onReset()
{
    QMessageBox::StandardButton reset;
    reset = QMessageBox::question(this, "Reset", "Are you sure you want to reset weights to default values?", QMessageBox::Yes | QMessageBox::No);
    if (reset == QMessageBox::No)
    {
        return;
    }
    for (auto it = weights.begin(); it != weights.end(); ++it)
    {
        it.value() = 5;
        if (it.key() == "Title")
        {
            it.value() = 10;
        }
        QSpinBox *spinBox = findChild<QSpinBox *>(it.key());
        if (spinBox)
        {
            spinBox->setValue(it.value());
        }
    }
};
void SettingsDisplay::onChangeColor()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button)
    {
        QColor color = QColorDialog::getColor(customPaletteData[button->objectName()], this, "Select Color");
        if (color.isValid())
        {
            customPaletteData[button->objectName()] = color;
            button->setStyleSheet("background-color: " + color.name() + ";");
            if (findChild<QComboBox *>("theme") && findChild<QComboBox *>("theme")->currentText() == "Custom")
            {
                customPaletteData[button->objectName()] = color;
                setAppPalette();
            }
        }
    }
}

void SettingsDisplay::onChangeTheme()
{
    QComboBox *themeComboBox = findChild<QComboBox *>("theme");
    if (themeComboBox)
    {
        selectedTheme = Settings::textToTheme(themeComboBox->currentText());
    }
    setAppPalette();
}

void SettingsDisplay::closeEvent(QCloseEvent *event)
{
    selectedTheme = Settings::getSettings().selectedTheme;
    customPaletteData = Settings::getSettings().customPaletteData;
    setAppPalette();
}

void SettingsDisplay::setAppPalette()
{
    Settings::setAppPalette(customPaletteData, selectedTheme);
}