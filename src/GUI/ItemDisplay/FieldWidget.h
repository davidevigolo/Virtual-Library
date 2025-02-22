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
};