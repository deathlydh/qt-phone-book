/********************************************************************************
** Form generated from reading UI file 'addcontactdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCONTACTDIALOG_H
#define UI_ADDCONTACTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddContactDialog
{
public:
    QLineEdit *telephoneLineEdit;
    QPushButton *addPhotoButton;
    QPushButton *saveButton;
    QLabel *text;
    QLineEdit *lastNameLineEdit;
    QLineEdit *firstNameLineEdit;

    void setupUi(QDialog *AddContactDialog)
    {
        if (AddContactDialog->objectName().isEmpty())
            AddContactDialog->setObjectName("AddContactDialog");
        AddContactDialog->resize(400, 300);
        telephoneLineEdit = new QLineEdit(AddContactDialog);
        telephoneLineEdit->setObjectName("telephoneLineEdit");
        telephoneLineEdit->setGeometry(QRect(10, 130, 361, 24));
        addPhotoButton = new QPushButton(AddContactDialog);
        addPhotoButton->setObjectName("addPhotoButton");
        addPhotoButton->setGeometry(QRect(10, 180, 91, 24));
        saveButton = new QPushButton(AddContactDialog);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(290, 260, 80, 24));
        text = new QLabel(AddContactDialog);
        text->setObjectName("text");
        text->setGeometry(QRect(140, 10, 131, 31));
        text->setTextFormat(Qt::PlainText);
        lastNameLineEdit = new QLineEdit(AddContactDialog);
        lastNameLineEdit->setObjectName("lastNameLineEdit");
        lastNameLineEdit->setGeometry(QRect(10, 50, 361, 24));
        firstNameLineEdit = new QLineEdit(AddContactDialog);
        firstNameLineEdit->setObjectName("firstNameLineEdit");
        firstNameLineEdit->setGeometry(QRect(10, 90, 361, 24));

        retranslateUi(AddContactDialog);

        QMetaObject::connectSlotsByName(AddContactDialog);
    } // setupUi

    void retranslateUi(QDialog *AddContactDialog)
    {
        AddContactDialog->setWindowTitle(QCoreApplication::translate("AddContactDialog", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\272\320\276\320\275\321\202\320\260\320\272\321\202\320\260", nullptr));
        telephoneLineEdit->setPlaceholderText(QCoreApplication::translate("AddContactDialog", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\274\320\265\321\200 \321\202\320\265\320\273\320\265\321\204\320\276\320\275\320\260", nullptr));
        addPhotoButton->setText(QCoreApplication::translate("AddContactDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\204\320\276\321\202\320\276", nullptr));
        saveButton->setText(QCoreApplication::translate("AddContactDialog", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        text->setText(QCoreApplication::translate("AddContactDialog", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\272\320\276\320\275\321\202\320\260\320\272\321\202\320\260", nullptr));
        lastNameLineEdit->setPlaceholderText(QCoreApplication::translate("AddContactDialog", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\204\320\260\320\274\320\270\320\273\320\270\321\216", nullptr));
        firstNameLineEdit->setPlaceholderText(QCoreApplication::translate("AddContactDialog", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\270\320\274\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddContactDialog: public Ui_AddContactDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCONTACTDIALOG_H
