#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QBuffer>
#include <QImageReader>
#include <QMessageBox>
#include "addcontactdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализация базы данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./PhoneNumberDB.db");
    if (!db.open()) {
        qDebug() << "Failed to open database";
    }

    // Создание таблицы, если она не существует
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS TelephoneBook(Firstname TEXT, Lastname TEXT, Telephone INT, Photo BLOB);");

    // Инициализация модели данных
    model = new QSqlTableModel(this, db);
    model->setTable("TelephoneBook");
    model->select();
    ui->tableView->setModel(model);

    // Установка заголовков таблицы
    model->setHeaderData(0, Qt::Horizontal, tr("First Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("Last Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Telephone"));

    // Скрытие столбца с изображением
    ui->tableView->hideColumn(3);

    // Инициализация таймера для фильтрации
    filterTimer = new QTimer(this);
    filterTimer->setInterval(300); // Устанавливаем интервал 300 мс
    filterTimer->setSingleShot(true); // Таймер однократного срабатывания
    connect(filterTimer, &QTimer::timeout, this, &MainWindow::applyFilter);
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

        model->setData(model->index(newRow, 0), dialog.getFirstName());
        model->setData(model->index(newRow, 1), dialog.getLastName());
        model->setData(model->index(newRow, 2), dialog.getTelephone());
        model->setData(model->index(newRow, 3), dialog.getPhoto());

        model->submitAll();
        model->select();
    }
}

void MainWindow::on_removeContactButton_clicked()
{
    if (currentRow == -1) {
        QMessageBox::warning(this, tr("Error"), tr("Please select a contact to delete."));
        return;
    }

    model->removeRow(currentRow);
    model->submitAll(); // Сохраняем изменения в базе данных
    model->select(); // Обновляем данные в QTableView
}

void MainWindow::on_searchLineEdit_textChanged(const QString &text)
{
    pendingFilter = text;
    filterTimer->start(); // Перезапуск таймера при каждом изменении текста
}

void MainWindow::applyFilter()
{
    QString filter = QString("Firstname LIKE '%%1%' COLLATE NOCASE OR Lastname LIKE '%%1%' COLLATE NOCASE OR Telephone LIKE '%%1%'")
                         .arg(pendingFilter);
    model->setFilter(filter);
    model->select();
}





void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();
    displayContactImage(index); // Вызов метода отображения изображения
}

void MainWindow::displayContactImage(const QModelIndex &index)
{
    QModelIndex photoIndex = model->index(index.row(), 3); // Индекс столбца Photo
    QByteArray imageData = model->data(photoIndex).toByteArray();

    QPixmap pixmap;
    pixmap.loadFromData(imageData);

    // Увеличиваем размер изображения для отображения в QLabel
    QPixmap largePixmap = pixmap.scaled(1000, 1000, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->contactImageLabel->setPixmap(largePixmap);
    ui->contactImageLabel->setScaledContents(true);
}
