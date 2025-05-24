#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "zadanie.h"
#include <fstream>
#include <QTableWidgetItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList dni = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(dni);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);
    loadZadania();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadZadania() {
    zadania.clear();
    std::ifstream plik("zadania.txt");
    std::string linia;
    while (std::getline(plik, linia)) {
        if (!linia.empty()) {
            zadania.push_back(deserializeZadanie(linia));
        }
    }
    refreshTable();
}

void MainWindow::saveZadaniaToFile() {
    std::ofstream plik("zadania.txt", std::ios::trunc);
    for (const auto& z : zadania) {
        plik << serializeZadanie(z) << "\n";
    }
}

void MainWindow::refreshTable() {
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(static_cast<int>(zadania.size()));

    for (int i = 0; i < zadania.size(); ++i) {
        const Zadanie& z = zadania[i];
        int dzien = static_cast<int>(z.getDzien());

        QString tekst = QString("%1:%2 - %3:%4\nPriorytet: %5\n%6")
                            .arg(z.getHrozpoczecia(), 2, 10, QLatin1Char('0'))
                            .arg(z.getMinRozpoczecia(), 2, 10, QLatin1Char('0'))
                            .arg(z.getHZakonczenia(), 2, 10, QLatin1Char('0'))
                            .arg(z.getMinZakonczenia(), 2, 10, QLatin1Char('0'))
                            .arg(z.getPriorytet())
                            .arg(QString::fromStdString(z.getNotatka()));

        QTableWidgetItem* item = new QTableWidgetItem(tekst);
        ui->tableWidget->setItem(i, dzien, item);
    }
}

void MainWindow::on_pushButton_clicked() {
    // Dla uproszczenia - dane testowe
    Zadanie z(Zadanie::Poniedzialek, 8, 30, 10, 0, 1, "Spotkanie z klientem");
    zadania.push_back(z);
    saveZadaniaToFile();
    refreshTable();
}

void MainWindow::on_pushButton_2_clicked() {
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0 && currentRow < zadania.size()) {
        zadania.erase(zadania.begin() + currentRow);
        saveZadaniaToFile();
        refreshTable();
    } else {
        QMessageBox::warning(this, "Błąd", "Nie wybrano zadania do usunięcia.");
    }
}


