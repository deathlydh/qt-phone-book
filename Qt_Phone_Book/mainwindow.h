#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QLabel> // Добавьте эту строку
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addContactButton_clicked();
    void on_removeContactButton_clicked();
    void on_searchLineEdit_textChanged(const QString &text);
    void on_tableView_clicked(const QModelIndex &index);


    void applyFilter();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;

    int currentRow;
    QTimer *filterTimer;
    QString pendingFilter;

    void displayContactImage(const QModelIndex &index); // Добавьте эту строку
};

#endif // MAINWINDOW_H
