#include <FieldWidget.h>
#include <QVBoxLayout>
#include <Settings.h>
#include <qmessagebox.h>
#include <QResizeEvent>
#include <QCheckBox>
#include <QSizePolicy>

FieldWidget::FieldWidget(const QString& fieldName, const QVariant& fieldValue, FieldType fieldType, QWidget *parent) : QWidget(parent), fieldType(fieldType) {
    if(fieldType == FieldType::TEXT){
        QLineEdit* lineEdit = new QLineEdit(this);
        lineEdit->setText(fieldValue.toString());
        inputWidget = lineEdit;
    }else if(fieldType == FieldType::INTEGER){
        QSpinBox* uNumberSpinBox = new QSpinBox(this);
        uNumberSpinBox->setValue(fieldValue.toInt());
        uNumberSpinBox->setRange(0, INT32_MAX);
        inputWidget = uNumberSpinBox;
    }else if(fieldType == FieldType::DOUBLE){
        QDoubleSpinBox* dNumberSpinBox = new QDoubleSpinBox(this);
        dNumberSpinBox->setValue(fieldValue.toDouble());
        dNumberSpinBox->setRange(0, 10000000);
        inputWidget = dNumberSpinBox;
    }else if(fieldType == FieldType::BOOL){
        QCheckBox* checkBox = new QCheckBox(this);
        checkBox->setChecked(fieldValue.toBool());
        inputWidget = checkBox;
    }else if(fieldType == FieldType::TAGS){
        QLineEdit* lineEdit = new QLineEdit(this);
        QString concatenatedValues;
        QStringList tags = fieldValue.toStringList();
        for (int i = 0; i < tags.size(); ++i) {
            concatenatedValues += QString(tags[i]);
            if (i != tags.size() - 1) {
                concatenatedValues += QString(", ");
            }
        }
        lineEdit->setText(concatenatedValues);
        inputWidget = lineEdit;
    }

    inputWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    // Create the label
    fieldLabel = new QLabel(this);
    fieldLabel->setText(QString(fieldName));
    layout->addWidget(fieldLabel, 0, Qt::AlignLeft);
    layout->addWidget(inputWidget, 0, Qt::AlignLeft);

    // Set the layout
    setLayout(layout);
}

QString FieldWidget::getFieldName() const
{
    return fieldLabel->text();
}

QVariant FieldWidget::getFieldValue() const
{
    switch (fieldType) {
        case FieldType::TEXT:
            return static_cast<QLineEdit*>(inputWidget)->text();
        case FieldType::INTEGER:
            return static_cast<QSpinBox*>(inputWidget)->value();
        case FieldType::DOUBLE:
            return static_cast<QDoubleSpinBox*>(inputWidget)->value();
        case FieldType::BOOL:
            return static_cast<QCheckBox*>(inputWidget)->isChecked();
        case FieldType::TAGS:
            return static_cast<QLineEdit*>(inputWidget)->text();
    }
    return QVariant();
}


void FieldWidget::setReadOnly(bool readOnly)
{
    inputWidget->setEnabled(!readOnly);
}

void FieldWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    inputWidget->setFixedWidth(event->size().width() - fieldLabel->sizeHint().width() - layout()->spacing());
}