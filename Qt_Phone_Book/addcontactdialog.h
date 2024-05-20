#ifndef ADDCONTACTDIALOG_H
#define ADDCONTACTDIALOG_H

#include <QDialog>

namespace Ui {
class AddContactDialog;
}

class AddContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddContactDialog(QWidget *parent = nullptr);
    ~AddContactDialog();

    QString getLastName() const;
    QString getFirstName() const;
    QString getTelephone() const;
    QByteArray getPhoto() const;

private slots:
    void on_addPhotoButton_clicked();
    void on_saveButton_clicked();

private:
    Ui::AddContactDialog *ui;
    QByteArray photoData;
};

#endif // ADDCONTACTDIALOG_H
