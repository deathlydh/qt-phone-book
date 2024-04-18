#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./phone_numberDB.db");
    if(db.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("no open");
    }

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE TelephoneBook(Firstname TEXT, Lastname TEXT, Telephone INT);");


    model = new QSqlTableModel(this, db);
    model->setTable("TelephoneBook");
    model->select();

    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Вставляем новую строку в модель данных
    int newRow = model->rowCount();
    model->insertRow(newRow);

    // Устанавливаем значения по умолчанию для новой строки
    QModelIndex index = model->index(newRow, 0); // Индекс новой строки, столбец Firstname
    model->setData(index, QVariant()); // Устанавливаем значение по умолчанию (пустое) для Firstname
    index = model->index(newRow, 1); // Индекс столбца Lastname
    model->setData(index, QVariant()); // Устанавливаем значение по умолчанию (пустое) для Lastname
    index = model->index(newRow, 2); // Индекс столбца Telephone
    model->setData(index, QVariant()); // Устанавливаем значение по умолчанию (пустое) для Telephone

    // Сигнализируем об изменении данных и обновляем представление
    model->submitAll(); // или model->submit(), в зависимости от вашего конкретного случая

    // Обновляем вид
    ui->tableView->scrollToBottom(); // Прокручиваем до новой строки, чтобы она была видима

}


void MainWindow::on_pushButton_2_clicked()
{
    model->removeRow(row);
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

