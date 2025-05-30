#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "oknodailogowe_dodajtask.h"
#include "task.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadFilesFromFile("zadania.txt");

    QStringList days = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(days);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Add_clicked()
{
    DialogWindow_AddTask dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Task newTask = dialog.getTask();

        newTask.saveToFile("zadania.txt");

        QString text =
            "Tytuł: " + newTask.getTitle() + "\n" +
            "priority: " + QString::number(newTask.getPriority()) + "\n" +
            "note: " + newTask.getNote();
        QString day = newTask.getDay();

        QStringList days = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
        int column = days.indexOf(day);
        if (column == -1) return;

        int daysfreeVerse = -1;
        for (int r = 0; r < ui->tableWidget->rowCount(); ++r) {
            if (ui->tableWidget->item(r, column) == nullptr) {
                daysfreeVerse = r;
                break;
            }
        }

        if (daysfreeVerse != -1) {
            QTableWidgetItem *item = new QTableWidgetItem(text);
            item->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
            ui->tableWidget->setItem(daysfreeVerse, column, item);
        }
    }
}

void MainWindow::loadFilesFromFile(const QString &path)
{
    QFile plik(path);
    if (!plik.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&plik);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList data = line.split('|');

        if (data.size() != 4)
            continue;

        QString title = data[0];
        QString day = data[1];
        int priority = data[2].toInt();
        QString note = data[3];

        Task task(title, day, priority, note);

        QString text =
            "Tytuł: " + task.getTitle() + "\n" +
            "Priorytet: " + QString::number(task.getPriority()) + "\n" +
            "Notatka: " + task.getNote();

        QStringList days = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
        int column = days.indexOf(task.getDay());
        if (column == -1) continue;

        int daysfreeVerse = -1;
        for (int r = 0; r < ui->tableWidget->rowCount(); ++r) {
            if (ui->tableWidget->item(r, column) == nullptr) {
                daysfreeVerse = r;
                break;
            }
        }

        if (daysfreeVerse != -1) {
            QTableWidgetItem *item = new QTableWidgetItem(text);
            item->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
            ui->tableWidget->setItem(daysfreeVerse, column, item);
        }
    }

    plik.close();
}

void MainWindow::saveAllTasksToFile(const QString &path)
{
    QFile plik(path);
    if (!plik.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&plik);

    QStringList days = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};

    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            QTableWidgetItem *item = ui->tableWidget->item(row, col);
            if (!item) continue;

            QString text = item->text();
            QStringList lines = text.split("\n");

            QString title = lines[0].mid(QString("Tytuł: ").length());
            int priority = lines[1].mid(QString("priority: ").length()).toInt();
            QString note = lines[2].mid(QString("note: ").length());
            QString day = days[col];

            out << title << "|" << day << "|" << priority << "|" << note << "\n";
        }
    }

    plik.close();
}


void MainWindow::on_Edit_clicked()
{
    QTableWidgetItem *item = ui->tableWidget->currentItem();
    if (!item)
        return;

    int row = ui->tableWidget->row(item);
    int col = ui->tableWidget->column(item);

    QString text = item->text();
    QStringList lines = text.split("\n");

    if (lines.size() != 3) return;

    QString title = lines[0].mid(QString("Tytuł: ").length());
    int priority = lines[1].mid(QString("priority: ").length()).toInt();
    QString note = lines[2].mid(QString("note: ").length());
    QStringList days = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
    QString day = days[col];

    Task oldtask(title, day, priority, note);
    DialogWindow_AddTask dialog(this);
    dialog.setTask(oldtask);

    if (dialog.exec() == QDialog::Accepted) {
        Task newtask = dialog.getTask();

        QString newtext =
            "Tytuł: " + newtask.getTitle() + "\n" +
            "priority: " + QString::number(newtask.getPriority()) + "\n" +
            "note: " + newtask.getNote();

        ui->tableWidget->setItem(row, col, nullptr);

        int newcolumn = days.indexOf(newtask.getDay());

        if (newcolumn == -1) return;

        int newRow = -1;
        for (int r = 0; r < ui->tableWidget->rowCount(); ++r) {
            if (ui->tableWidget->item(r, newcolumn) == nullptr) {
                newRow = r;
                break;
            }
        }

        if (newRow != -1) {
            QTableWidgetItem *newItem = new QTableWidgetItem(newtext);
            newItem->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
            ui->tableWidget->setItem(newRow, newcolumn, newItem);
        }

        saveAllTasksToFile("zadania.txt");
    }
}

void MainWindow::on_Delete_clicked()
{
    QTableWidgetItem *item = ui->tableWidget->currentItem();
    if (!item)
        return;

    int row = ui->tableWidget->row(item);
    int col = ui->tableWidget->column(item);

    ui->tableWidget->setItem(row, col, nullptr);

    saveAllTasksToFile("zadania.txt");
}

