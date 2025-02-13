#include "ScrollPanel.h"

ScrollPanel::ScrollPanel(int index, QWidget *parent ) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this); //verticale così il tag va sopra

    QHBoxLayout *panelLayout = new QHBoxLayout;
    for (int j = 0; j < 5; ++j) {
        QVBoxLayout *buttonLayout = new QVBoxLayout;

        QPushButton *button = new QPushButton;
        //button->setIcon(QIcon("../inception_prova.jpg"));
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        button->setStyleSheet("background-color: black;");
        buttonLayout->addWidget(button, 0, Qt::AlignTop);

        QPushButton::connect(button, &QPushButton::clicked, [button](){
            //button->setIcon(QIcon("../toro_prova.png"));
            button->setStyleSheet("background-color: white;");
        });

        QLabel *buttonLabel = new QLabel(QString("Button %1").arg(j + 1));
        buttonLabel->setAlignment(Qt::AlignCenter);
        buttonLabel->setStyleSheet("background-color: white;");
        buttonLayout->addWidget(buttonLabel);

        panelLayout->addLayout(buttonLayout);
    }

    layout->addLayout(panelLayout);
    setLayout(layout);
    setStyleSheet("background-color: gray;");
}