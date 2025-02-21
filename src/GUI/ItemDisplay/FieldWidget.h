#pragma once
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>

class FieldWidget : public QWidget
{
    Q_OBJECT
private:
    QLabel *fieldLabel;
    QLineEdit *fieldLineEdit;
    QSpinBox *uNumberBox;
    QDoubleSpinBox *dNumberBox;
public:
    FieldWidget(const QString& fieldName, const QString& fieldValue, QWidget *parent = nullptr);
    FieldWidget(const QString& fieldName, const std::vector<std::string>& fieldValue, QWidget *parent = nullptr);//for the tags field
    FieldWidget(const QString& filedName, const unsigned int& fieldValue, QWidget *parent = nullptr);//for the integers values
    FieldWidget(const QString& filedName, const double& fieldValue, QWidget *parent = nullptr);//for the integers values
    QString getFieldName() const;
    QString getLineEditValue() const;
    unsigned int getSpinBoxValue() const;
    double getDoubleSpinBoxValue() const;
    void setReadOnly(bool);
};