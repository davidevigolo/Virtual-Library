#include <ItemDisplay.h>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <GridVisitor.h>

ItemDisplay::ItemDisplay(MediaItem *item, QWidget* parent) : QWidget(parent)
{
    this->item = item;


    QLabel *imageLabel = new QLabel(this);
    QPixmap image(item->getImage().c_str());
    imageLabel->setPixmap(image);


    QPushButton *goBackButton = new QPushButton("Go Back", this);
    goBackButton->setStyleSheet("background-color: red; color: black;");
    goBackButton->setFixedWidth(image.width() / 4);

    connect(goBackButton, &QPushButton::clicked, this, &ItemDisplay::onGoBack);
    connect(this, &ItemDisplay::onGoBack, this, &ItemDisplay::itemDisplayClosed);


    QWidget *buttonWidget = new QWidget(this);
    QHBoxLayout *buttonsLayout = new QHBoxLayout();


    QPushButton *editButton = new QPushButton("Edit", buttonWidget);
    QPushButton *deleteButton = new QPushButton("Delete", buttonWidget);

    editButton->setStyleSheet("background-color: yellow; color: black;");
    editButton->setFixedWidth(image.width() / 4);
    deleteButton->setStyleSheet("background-color: green; color: black;");
    deleteButton->setFixedWidth(image.width() / 4);

    buttonsLayout->addStretch(); // Add stretchable space before buttons
    buttonsLayout->addWidget(editButton);
    buttonsLayout->addWidget(deleteButton);

    connect(editButton, &QPushButton::clicked, this, &ItemDisplay::onEdit);
    connect(deleteButton, &QPushButton::clicked, this, &ItemDisplay::onDeletion);
    
    buttonWidget->setLayout(buttonsLayout);
    buttonsLayout->addWidget(editButton);
    buttonsLayout->addWidget(deleteButton);
    

    QWidget *fields = new QWidget(this);
    fields->setFixedHeight(image.height());
    GridVisitor visitor(fields);
    item->accept(&visitor);


    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(goBackButton, 0, 0);
    layout->addWidget(buttonWidget, 0, 1);
    layout->addWidget(imageLabel, 1, 0);
    layout->addWidget(fields, 1, 1);    
    

    setLayout(layout);
}

void ItemDisplay::onEdit()
{
    emit itemChanged(item);
}

void ItemDisplay::onDeletion()
{
    emit itemDeleted(item);
}

void ItemDisplay::onGoBack()
{
    emit itemDisplayClosed();
}