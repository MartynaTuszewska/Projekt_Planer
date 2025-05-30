#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "oknodailogowe_dodajzadanie.h"
#include "zadanie.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadFilesFromFile("zadania.txt");

    QStringList dni = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(dni);

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
            "Priorytet: " + QString::number(newTask.getPriority()) + "\n" +
            "Notatka: " + newTask.getNote();
        QString dzien = newTask.getDay();

        QStringList dni = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
        int column = dni.indexOf(dzien);
        if (column == -1) return;

        int wolnyWiersz = -1;
        for (int r = 0; r < ui->tableWidget->rowCount(); ++r) {
            if (ui->tableWidget->item(r, column) == nullptr) {
                wolnyWiersz = r;
                break;
            }
        }

        if (wolnyWiersz != -1) {
            QTableWidgetItem *item = new QTableWidgetItem(text);
            item->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
            ui->tableWidget->setItem(wolnyWiersz, column, item);
        }
    }
}

void MainWindow::loadFilesFromFile(const QString &sciezka)
{
    QFile plik(sciezka);
    if (!plik.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&plik);
    while (!in.atEnd()) {
        QString linia = in.readLine();
        QStringList dane = linia.split('|');

        if (dane.size() != 4)
            continue;

        QString tytul = dane[0];
        QString dzien = dane[1];
        int priorytet = dane[2].toInt();
        QString notatka = dane[3];

        Task zadanie(tytul, dzien, priorytet, notatka);

        QString text =
            "Tytuł: " + zadanie.getTitle() + "\n" +
            "Priorytet: " + QString::number(zadanie.getPriority()) + "\n" +
            "Notatka: " + zadanie.getNote();

        QStringList dni = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
        int column = dni.indexOf(zadanie.getDay());
        if (column == -1) continue;

        int wolnyWiersz = -1;
        for (int r = 0; r < ui->tableWidget->rowCount(); ++r) {
            if (ui->tableWidget->item(r, column) == nullptr) {
                wolnyWiersz = r;
                break;
            }
        }

        if (wolnyWiersz != -1) {
            QTableWidgetItem *item = new QTableWidgetItem(text);
            item->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
            ui->tableWidget->setItem(wolnyWiersz, column, item);
        }
    }

    plik.close();
}

void MainWindow::saveAllTasksToFile(const QString &sciezka)
{
    QFile plik(sciezka);
    if (!plik.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&plik);

    QStringList dni = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};

    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            QTableWidgetItem *item = ui->tableWidget->item(row, col);
            if (!item) continue;

            QString text = item->text();
            QStringList linie = text.split("\n");

            QString tytul = linie[0].mid(QString("Tytuł: ").length());
            int priorytet = linie[1].mid(QString("Priorytet: ").length()).toInt();
            QString notatka = linie[2].mid(QString("Notatka: ").length());
            QString dzien = dni[col];

            out << tytul << "|" << dzien << "|" << priorytet << "|" << notatka << "\n";
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
    QStringList linie = text.split("\n");

    if (linie.size() != 3) return;

    QString tytul = linie[0].mid(QString("Tytuł: ").length());
    int priorytet = linie[1].mid(QString("Priorytet: ").length()).toInt();
    QString notatka = linie[2].mid(QString("Notatka: ").length());
    QStringList dni = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
    QString dzien = dni[col];

    Task staryZadanie(tytul, dzien, priorytet, notatka);
    DialogWindow_AddTask dialog(this);
    dialog.setTask(staryZadanie);

    if (dialog.exec() == QDialog::Accepted) {
        Task nowyZadanie = dialog.getTask();

        QString nowytext =
            "Tytuł: " + nowyZadanie.getTitle() + "\n" +
            "Priorytet: " + QString::number(nowyZadanie.getPriority()) + "\n" +
            "Notatka: " + nowyZadanie.getNote();

        ui->tableWidget->setItem(row, col, nullptr);

        int nowacolumn = dni.indexOf(nowyZadanie.getDay());

        if (nowacolumn == -1) return;

        int nowyWiersz = -1;
        for (int r = 0; r < ui->tableWidget->rowCount(); ++r) {
            if (ui->tableWidget->item(r, nowacolumn) == nullptr) {
                nowyWiersz = r;
                break;
            }
        }

        if (nowyWiersz != -1) {
            QTableWidgetItem *nowyItem = new QTableWidgetItem(nowytext);
            nowyItem->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
            ui->tableWidget->setItem(nowyWiersz, nowacolumn, nowyItem);
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

