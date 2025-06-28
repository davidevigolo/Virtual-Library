#pragma once
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QIcon>
#include <QResizeEvent>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <ButtonWidget.h>

/**
 * @class CustomScrollArea
 * @brief A custom scroll area that inherits from QScrollArea.
 *
 * This class provides a custom implementation of a scroll area making it
 * call the resizeEvent function on its widget when the window is resized.
 *
 * @param parent The parent widget of the scroll area. Defaults to nullptr.
 *
 * @fn CustomScrollArea::CustomScrollArea(QWidget *parent)
 * @brief Constructor for CustomScrollArea.
 * @param parent The parent widget of the scroll area. Defaults to nullptr.
 */
class CustomScrollArea : public QScrollArea {
public:
    CustomScrollArea(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
};