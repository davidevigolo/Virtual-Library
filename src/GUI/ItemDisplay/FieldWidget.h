#pragma once
#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class FieldWidget : public QWidget
{
    Q_OBJECT
private:
    QLabel *fieldLabel;
    QLineEdit *fieldLineEdit;

public:
    FieldWidget(const QString& fieldName, const QString& fieldValue, QWidget *parent = nullptr);
    FieldWidget(const QString& fieldName, const std::vector<std::string>& fieldValue, QWidget *parent = nullptr);//for the tags field
    void setReadOnly(bool);
};