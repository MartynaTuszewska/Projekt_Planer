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

    wczytajZadaniaZPliku("zadania.txt");

    QStringList dni = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(dni);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Dodaj_clicked()
{
    OknoDailogowe_DodajZadanie dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Zadanie noweZadanie = dialog.getZadanie();

        noweZadanie.zapiszDoPliku("zadania.txt");

        QString tekst =
            "Tytuł: " + noweZadanie.getTytul() + "\n" +
            "Priorytet: " + QString::number(noweZadanie.getPriorytet()) + "\n" +
            "Notatka: " + noweZadanie.getNotatka();
        QString dzien = noweZadanie.getDzien();

        QStringList dni = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
        int kolumna = dni.indexOf(dzien);
        if (kolumna == -1) return;

        int wolnyWiersz = -1;
        for (int r = 0; r < ui->tableWidget->rowCount(); ++r) {
            if (ui->tableWidget->item(r, kolumna) == nullptr) {
                wolnyWiersz = r;
                break;
            }
        }

        if (wolnyWiersz != -1) {
            QTableWidgetItem *item = new QTableWidgetItem(tekst);
            item->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
            ui->tableWidget->setItem(wolnyWiersz, kolumna, item);
        }
    }
}

void MainWindow::wczytajZadaniaZPliku(const QString &sciezka)
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

        Zadanie zadanie(tytul, dzien, priorytet, notatka);

        QString tekst =
            "Tytuł: " + zadanie.getTytul() + "\n" +
            "Priorytet: " + QString::number(zadanie.getPriorytet()) + "\n" +
            "Notatka: " + zadanie.getNotatka();

        QStringList dni = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
        int kolumna = dni.indexOf(zadanie.getDzien());
        if (kolumna == -1) continue;

        int wolnyWiersz = -1;
        for (int r = 0; r < ui->tableWidget->rowCount(); ++r) {
            if (ui->tableWidget->item(r, kolumna) == nullptr) {
                wolnyWiersz = r;
                break;
            }
        }

        if (wolnyWiersz != -1) {
            QTableWidgetItem *item = new QTableWidgetItem(tekst);
            item->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
            ui->tableWidget->setItem(wolnyWiersz, kolumna, item);
        }
    }

    plik.close();
}

void MainWindow::zapiszWszystkieZadaniaDoPliku(const QString &sciezka)
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

            QString tekst = item->text();
            QStringList linie = tekst.split("\n");

            QString tytul = linie[0].mid(QString("Tytuł: ").length());
            int priorytet = linie[1].mid(QString("Priorytet: ").length()).toInt();
            QString notatka = linie[2].mid(QString("Notatka: ").length());
            QString dzien = dni[col];

            out << tytul << "|" << dzien << "|" << priorytet << "|" << notatka << "\n";
        }
    }

    plik.close();
}


void MainWindow::on_Edytuj_clicked()
{
    QTableWidgetItem *item = ui->tableWidget->currentItem();
    if (!item)
        return;

    int row = ui->tableWidget->row(item);
    int col = ui->tableWidget->column(item);

    QString tekst = item->text();
    QStringList linie = tekst.split("\n");

    if (linie.size() != 3) return;

    QString tytul = linie[0].mid(QString("Tytuł: ").length());
    int priorytet = linie[1].mid(QString("Priorytet: ").length()).toInt();
    QString notatka = linie[2].mid(QString("Notatka: ").length());
    QStringList dni = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
    QString dzien = dni[col];

    Zadanie staryZadanie(tytul, dzien, priorytet, notatka);
    OknoDailogowe_DodajZadanie dialog(this);
    dialog.ustawZadanie(staryZadanie);

    if (dialog.exec() == QDialog::Accepted) {
        Zadanie nowyZadanie = dialog.getZadanie();

        QString nowyTekst =
            "Tytuł: " + nowyZadanie.getTytul() + "\n" +
            "Priorytet: " + QString::number(nowyZadanie.getPriorytet()) + "\n" +
            "Notatka: " + nowyZadanie.getNotatka();

        ui->tableWidget->setItem(row, col, nullptr);

        int nowaKolumna = dni.indexOf(nowyZadanie.getDzien());

        if (nowaKolumna == -1) return;

        int nowyWiersz = -1;
        for (int r = 0; r < ui->tableWidget->rowCount(); ++r) {
            if (ui->tableWidget->item(r, nowaKolumna) == nullptr) {
                nowyWiersz = r;
                break;
            }
        }

        if (nowyWiersz != -1) {
            QTableWidgetItem *nowyItem = new QTableWidgetItem(nowyTekst);
            nowyItem->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
            ui->tableWidget->setItem(nowyWiersz, nowaKolumna, nowyItem);
        }

        zapiszWszystkieZadaniaDoPliku("zadania.txt");
    }
}

void MainWindow::on_Usun_clicked()
{
    QTableWidgetItem *item = ui->tableWidget->currentItem();
    if (!item)
        return;

    int row = ui->tableWidget->row(item);
    int col = ui->tableWidget->column(item);

    ui->tableWidget->setItem(row, col, nullptr);

    zapiszWszystkieZadaniaDoPliku("zadania.txt");
}

