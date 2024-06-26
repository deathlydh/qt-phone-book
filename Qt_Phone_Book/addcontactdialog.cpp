#include "addcontactdialog.h"
#include "ui_addcontactdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QBuffer>
#include <QRegularExpressionValidator>

AddContactDialog::AddContactDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddContactDialog)
{
    ui->setupUi(this);
    this->setFixedSize(400, 300);

    // Установка валидатора для поля телефона
    QRegularExpression regExp("[+0-9]*");
    ui->telephoneLineEdit->setValidator(new QRegularExpressionValidator(regExp, this));
}

AddContactDialog::~AddContactDialog()
{
    delete ui;
}

QString AddContactDialog::getLastName() const
{
    return ui->lastNameLineEdit->text();
}

QString AddContactDialog::getFirstName() const
{
    return ui->firstNameLineEdit->text();
}

QString AddContactDialog::getTelephone() const
{
    return ui->telephoneLineEdit->text();
}

QByteArray AddContactDialog::getPhoto() const
{
    return photoData;
}

void AddContactDialog::on_addPhotoButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (!image.isNull()) {
            QImage smallImage = image.scaled(1000, 1000, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QBuffer buffer(&photoData);
            buffer.open(QIODevice::WriteOnly);
            smallImage.save(&buffer, "PNG");
        }
    }
}

void AddContactDialog::on_saveButton_clicked()
{
    if (getFirstName().isEmpty() || getLastName().isEmpty() || getTelephone().isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Please fill in all fields."));
        return;
    }
    accept();
}
