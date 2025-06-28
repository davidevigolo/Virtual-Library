#pragma once
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>

enum FieldType {
    TEXT,
    INTEGER,
    DOUBLE,
    BOOL,
    TAGS
};

/*
 * @class FieldWidget
 * @brief A widget for displaying and editing a specific field of a media item.
 *
 * The FieldWidget class provides a user interface element for displaying and editing
 * a specific field of a media item. It includes a label for the field name and an
 * input widget for the field value, which can be of different types (text, integer,
 * double, boolean, or tags). The widget also handles resizing and read-only states.
 */
class FieldWidget : public QWidget
{
    Q_OBJECT
private:
    QLabel *fieldLabel;
    FieldType fieldType;
    QWidget* inputWidget;
public:
    FieldWidget(const QString& fieldName, const QVariant& fieldValue, FieldType fieldType, QWidget *parent = nullptr);
    QVariant getFieldValue() const;
    QString getFieldName() const;
    void setReadOnly(bool);
protected:
    void resizeEvent(QResizeEvent* event) override;
};