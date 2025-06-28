#include <ItemDisplay.h>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <GridVisitor.h>
#include <QMessageBox>
#include <QFileInfo>
#include "EditMaker.h"
#include "FieldWidget.h"
#include <qfiledialog.h>
#include <QDebug>

ItemDisplay::ItemDisplay(MediaItem *item, QWidget *parent, bool newItem) : QWidget(parent), newItem(newItem)
{
    this->item = item;

    imagePath = QString::fromStdString(item->getImage());
    imageButton = new ImageButton(this, imagePath);

    QFileInfo fileInfo(imagePath);
    if (fileInfo.exists())
    {
        imageButton->setIcon(imagePath);
    }
    else
    {
        imageButton->setIcon(":/images/resources/no_image.jpeg");
    }
    imageButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    imageButton->setEnabled(false);

    QPushButton *goBackButton = new QPushButton("Go Back", this);
    goBackButton->setStyleSheet("background-color: red; color: black;");
    goBackButton->setFixedWidth(imageButton->width());

    connect(goBackButton, &QPushButton::clicked, this, &ItemDisplay::onGoBack);
    connect(imageButton, &ImageButton::imageButtonClicked, this, &ItemDisplay::onImageButtonClicked);

    QWidget *buttonWidget = new QWidget(this);
    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    editButton = new QPushButton("Edit", buttonWidget);
    deleteButton = new QPushButton("Delete", buttonWidget);

    editButton->setStyleSheet("background-color: yellow; color: black;");
    editButton->setFixedWidth(imageButton->width());
    deleteButton->setStyleSheet("background-color: green; color: black;");
    deleteButton->setFixedWidth(imageButton->width());

    saveButton = new QPushButton("Save", buttonWidget);
    cancelButton = new QPushButton("Cancel", buttonWidget);

    saveButton->setStyleSheet("background-color: yellow; color: black;");
    saveButton->setFixedWidth(imageButton->width());
    cancelButton->setStyleSheet("background-color: green; color: black;");
    cancelButton->setFixedWidth(imageButton->width());

    saveButton->hide();
    cancelButton->hide();

    connect(saveButton, &QPushButton::clicked, this, &ItemDisplay::onSave);
    connect(cancelButton, &QPushButton::clicked, this, &ItemDisplay::onCancel);

    buttonsLayout->addStretch(); // Add stretchable space before buttons
    buttonsLayout->addWidget(editButton);
    buttonsLayout->addWidget(deleteButton);
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(cancelButton);

    connect(editButton, &QPushButton::clicked, this, &ItemDisplay::onEdit);
    connect(deleteButton, &QPushButton::clicked, this, &ItemDisplay::onDeletion);

    buttonWidget->setLayout(buttonsLayout);
    buttonsLayout->addWidget(editButton);
    buttonsLayout->addWidget(deleteButton);

    QWidget *fields = new QWidget(this);
    GridVisitor visitor(fields);
    item->accept(&visitor);

    for (auto field : findChildren<FieldWidget *>())
    {
        field->setReadOnly(true);
    }

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(goBackButton, 0, 0);
    layout->addWidget(buttonWidget, 0, 1);
    layout->addWidget(imageButton, 1, 0);
    layout->addWidget(fields, 1, 1);
    fields->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Policy::MinimumExpanding);

    setLayout(layout);

    if (newItem)
        onEdit();
}

void ItemDisplay::onEdit()
{
    editButton->hide();
    deleteButton->hide();
    imageButton->setEnabled(true);
    cancelButton->show();
    saveButton->show();
    // segnalare a fields che è stato premuto
    for (auto field : findChildren<FieldWidget *>())
    {
        field->setReadOnly(false);
    }
    emit itemChanged(item);
}

void ItemDisplay::onCancel()
{
    editButton->show();
    deleteButton->show();
    imageButton->setEnabled(false);
    cancelButton->hide();
    saveButton->hide();
    // segnalare a fields che è stato premuto
    for (auto field : findChildren<FieldWidget *>())
    {
        layout()->removeWidget(field);
        delete field;
    }
    if (newItem)
    {
        onGoBack();
        return;
    }
    QWidget *fields = new QWidget(this);
    fields->setFixedHeight(imageButton->height());
    GridVisitor visitor(fields);
    item->accept(&visitor);
    static_cast<QGridLayout *>(layout())->addWidget(fields, 1, 1);
}

void ItemDisplay::onSave()
{
    editButton->show();
    deleteButton->show();
    cancelButton->hide();
    saveButton->hide();
    imageButton->setEnabled(false);
    EditMaker editMaker;
    for (auto field : findChildren<FieldWidget *>())
    {
        editMaker.makeEdit(field, item);
        field->setReadOnly(true);
    }
    if (!imagePath.isEmpty())
    {
        item->setImage(imagePath.toStdString());
    }
    if(newItem){
        newItem = false;
        emit itemChanged(item);
    }
}

void ItemDisplay::onDeletion()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete this item?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No)
    {
        return;
    }
    emit itemDeleted(item);
}

void ItemDisplay::onGoBack()
{
    if(newItem){
        emit itemDeleted(item);
        return;
    }
    emit itemDisplayClosed();
}

void ItemDisplay::onImageButtonClicked()
{
    imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Image Files (*.png *.jpg *.jpeg *.bmp *.gif *.pbm *.pgm *.ppm *.xbm *.xpm);;All Files (*)");
    if (imagePath.isEmpty())
    {
        return;
    }
    imageButton->setIcon(imagePath);
}