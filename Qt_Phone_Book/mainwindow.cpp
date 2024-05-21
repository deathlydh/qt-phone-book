#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addcontactdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QImageReader>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //this->setFixedSize(865, 638);

    // Инициализация базы данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./TelephoneBookDB.db");
    if (!db.open()) {
        qDebug() << "Failed to open database";
    }

    // Создание таблицы, если она не существует
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS TelephoneBook(Lastname TEXT, Firstname TEXT, Telephone TEXT, Photo BLOB);");

    // Инициализация модели данных
    model = new QSqlTableModel(this, db);
    model->setTable("TelephoneBook");
    model->setSort(0, Qt::AscendingOrder); // Сортировка по фамилии (Lastname)
    model->select();
    ui->tableView->setModel(model);

    // Установка заголовков таблицы
    model->setHeaderData(0, Qt::Horizontal, tr("Фамилия"));
    model->setHeaderData(1, Qt::Horizontal, tr("Имя"));
    model->setHeaderData(2, Qt::Horizontal, tr("Телефон"));

    // Скрытие столбца с фотографиями
    ui->tableView->setColumnHidden(3, true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addContactButton_clicked()
{
    AddContactDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        int newRow = model->rowCount();
        model->insertRow(newRow);

        QString lastName = dialog.getLastName();
        QString firstName = dialog.getFirstName();
        QString telephone = dialog.getTelephone();


        model->setData(model->index(newRow, 0), lastName);
        model->setData(model->index(newRow, 1), firstName);
        model->setData(model->index(newRow, 2), telephone);
        model->setData(model->index(newRow, 3), dialog.getPhoto());

        model->submitAll();
        model->select();
    }
}

void MainWindow::on_removeContactButton_clicked()
{
    int currentRow = ui->tableView->currentIndex().row();
    if (currentRow >= 0) {
        model->removeRow(currentRow);
        model->submitAll();
        model->select();
    }
}

void MainWindow::on_searchLineEdit_textChanged(const QString &text)
{
    QString filter = QString("(Lastname LIKE '%%1%' COLLATE NOCASE OR Firstname LIKE '%%1%' COLLATE NOCASE OR Telephone LIKE '%%1%')").arg(text);
    model->setFilter(filter);
    model->select();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    QByteArray photoData = model->data(model->index(row, 3)).toByteArray();

    if (!photoData.isEmpty()) {
        QPixmap pixmap;
        pixmap.loadFromData(photoData);
        ui->contactImageLabel->setPixmap(pixmap.scaled(ui->contactImageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        ui->contactImageLabel->clear();
    }
}
