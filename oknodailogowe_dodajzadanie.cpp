#include "oknodailogowe_dodajzadanie.h"
#include "ui_oknodailogowe_dodajzadanie.h"

DialogWindow_AddTask::DialogWindow_AddTask(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogWindow_AddTask)
{
    ui->setupUi(this);
    ui->dayDialog->addItems({"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"});
}

DialogWindow_AddTask::~DialogWindow_AddTask()
{
    delete ui;
}

Task DialogWindow_AddTask::getTask() const
{
    return Task(
        ui->titleDialog->text(),
        ui->dayDialog->currentText(),
        ui->priorityDialog->value(),
        ui->noteDialog->toPlainText()
        );
}

void DialogWindow_AddTask::setTask(const Task &zadanie)
{
    ui->titleDialog->setText(zadanie.getTitle());
    ui->dayDialog->setCurrentText(zadanie.getDay());
    ui->priorityDialog->setValue(zadanie.getPriority());
    ui->noteDialog->setPlainText(zadanie.getNote());
}

