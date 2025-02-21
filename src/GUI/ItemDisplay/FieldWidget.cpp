#include <FieldWidget.h>
#include <QVBoxLayout>
#include <Settings.h>


FieldWidget::FieldWidget(const QString& fieldName, const QString& fieldValue, QWidget *parent) : QWidget(parent)
{
    dNumberBox = nullptr;
    uNumberBox = nullptr;
    // Create the layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // Create the label
    fieldLabel = new QLabel(this);
    fieldLabel->setText(QString(fieldName));
    layout->addWidget(fieldLabel, 0, Qt::AlignLeft);

    // Create the field
    fieldLineEdit = new QLineEdit(this);
    fieldLineEdit->setText(QString(fieldValue));
    layout->addWidget(fieldLineEdit, 0, Qt::AlignLeft);
    // Set the layout
    setLayout(layout);
}

FieldWidget::FieldWidget(const QString& fieldName, const std::vector<std::string>& fieldValue, QWidget *parent) : QWidget(parent) //for the tags field
{
    dNumberBox = nullptr;
    uNumberBox = nullptr;
    // Create the layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // Create the label
    fieldLabel = new QLabel(this);
    
    fieldLabel->setText(QString(fieldName));
    layout->addWidget(fieldLabel, 0, Qt::AlignLeft);

    /*
    Tags are stored in a QVector<QString> so we need to concatenate them into a single string
    */
    QString concatenatedValues;
    for (size_t i = 0; i < fieldValue.size(); ++i) {
        concatenatedValues += QString(fieldValue[i].c_str());
        if (i != fieldValue.size() - 1) {
            concatenatedValues += QString(", ");
        }
    }
    // Create the field
    fieldLineEdit = new QLineEdit(this);
    fieldLineEdit->setText(QString(concatenatedValues));
    layout->addWidget(fieldLineEdit, 0, Qt::AlignLeft);
    // Set the layout
    setLayout(layout);
}

FieldWidget::FieldWidget(const QString& fieldName, const unsigned int& fieldValue, QWidget *parent) : QWidget(parent) //for the tags field
{
    dNumberBox = nullptr;
    fieldLineEdit = nullptr;
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // Create the label
    fieldLabel = new QLabel(this);
    fieldLabel->setText(QString(fieldName));
    layout->addWidget(fieldLabel, 0, Qt::AlignLeft);

    // Create the field
    uNumberBox = new QSpinBox(this);
    uNumberBox->setValue(fieldValue);
    uNumberBox->setRange(0, 3000);
    layout->addWidget(uNumberBox, 0, Qt::AlignLeft);
    // Set the layout
    setLayout(layout);
}

FieldWidget::FieldWidget(const QString& fieldName, const double& fieldValue, QWidget *parent) : QWidget(parent) //for the tags field
{
    uNumberBox = nullptr;
    fieldLineEdit = nullptr;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // Create the label
    fieldLabel = new QLabel(this);
    fieldLabel->setText(QString(fieldName));
    layout->addWidget(fieldLabel, 0, Qt::AlignLeft);

    // Create the field
    dNumberBox = new QDoubleSpinBox(this);
    dNumberBox->setValue(fieldValue);
    dNumberBox->setRange(0, 50);//for the framerate
    layout->addWidget(dNumberBox, 0, Qt::AlignLeft);
    // Set the layout
    setLayout(layout);
}


QString FieldWidget::getFieldName() const
{
    return fieldLabel->text();
}

QString FieldWidget::getLineEditValue() const
{
    return fieldLineEdit->text();
}

unsigned int FieldWidget::getSpinBoxValue() const
{
    return uNumberBox->value();
}

double FieldWidget::getDoubleSpinBoxValue() const
{
    return dNumberBox->value();
}


void FieldWidget::setReadOnly(bool readOnly)
{
    if(dNumberBox != nullptr)
        dNumberBox->setReadOnly(readOnly);
    if(uNumberBox != nullptr)   
        uNumberBox->setReadOnly(readOnly);
    if(fieldLineEdit != nullptr)
        fieldLineEdit->setReadOnly(readOnly);
}