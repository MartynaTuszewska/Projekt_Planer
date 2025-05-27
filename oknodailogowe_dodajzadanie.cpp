#include "oknodailogowe_dodajzadanie.h"
#include "ui_oknodailogowe_dodajzadanie.h"

OknoDailogowe_DodajZadanie::OknoDailogowe_DodajZadanie(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OknoDailogowe_DodajZadanie)
{
    ui->setupUi(this);
    ui->dzienDialog->addItems({"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"});
}

OknoDailogowe_DodajZadanie::~OknoDailogowe_DodajZadanie()
{
    delete ui;
}

Zadanie OknoDailogowe_DodajZadanie::getZadanie() const
{
    return Zadanie(
        ui->tytulDialog->text(),
        ui->dzienDialog->currentText(),
        ui->priorytetDialog->value(),
        ui->notatkaDialog->toPlainText()
        );
}

void OknoDailogowe_DodajZadanie::ustawZadanie(const Zadanie &zadanie)
{
    ui->tytulDialog->setText(zadanie.getTytul());
    ui->dzienDialog->setCurrentText(zadanie.getDzien());
    ui->priorytetDialog->setValue(zadanie.getPriorytet());
    ui->notatkaDialog->setPlainText(zadanie.getNotatka());
}

