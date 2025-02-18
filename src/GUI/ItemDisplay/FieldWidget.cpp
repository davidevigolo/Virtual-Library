#include <FieldWidget.h>
#include <QVBoxLayout>


FieldWidget::FieldWidget(const QString& fieldName, const QString& fieldValue, QWidget *parent) : QWidget(parent)
{
    // Create the layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // Create the label
    fieldLabel = new QLabel(this);
    fieldLabel->setStyleSheet("QLabel { color : white; }");
    fieldLabel->setText(QString(fieldName));
    layout->addWidget(fieldLabel, 0, Qt::AlignLeft);

    // Create the field
    fieldLineEdit = new QLineEdit(this);
    fieldLineEdit->setStyleSheet("QLineEdit { color : white; }");
    fieldLineEdit->setPlaceholderText(QString(fieldValue));
    layout->addWidget(fieldLineEdit, 0, Qt::AlignLeft);
    // Set the layout
    setLayout(layout);
}

FieldWidget::FieldWidget(const QString& fieldName, const std::vector<std::string>& fieldValue, QWidget *parent) : QWidget(parent) //for the tags field
{
    // Create the layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // Create the label
    fieldLabel = new QLabel(this);
    fieldLabel->setStyleSheet("QLabel { color : white; }");
    
    fieldLabel->setText(QString(fieldName));
    layout->addWidget(fieldLabel, 0, Qt::AlignLeft);

    /*
    Tags are stored in a QVector<QString> so we need to concatenate them into a single string
    */
    QString concatenatedValues;
    for (int i = 0; i < fieldValue.size(); ++i) {
        concatenatedValues += QString(fieldValue[i].c_str());
        if (i != fieldValue.size() - 1) {
            concatenatedValues += QString(", ");
        }
    }
    // Create the field
    fieldLineEdit = new QLineEdit(this);
    fieldLineEdit->setStyleSheet("QLineEdit { color : white; }");
    fieldLineEdit->setPlaceholderText(QString(concatenatedValues));
    layout->addWidget(fieldLineEdit, 0, Qt::AlignLeft);
    // Set the layout
    setLayout(layout);
}

void FieldWidget::setReadOnly(bool readOnly)
{
    fieldLineEdit->setReadOnly(readOnly);
}