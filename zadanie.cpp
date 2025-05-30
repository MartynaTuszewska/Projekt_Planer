#include "zadanie.h"
#include <QFile>
#include <QTextStream>

Task::Task()
    : priority(0)
{}

Task::Task(const QString &tytul, const QString &dzien, int priorytet, const QString &notatka)
{
    this->title = tytul;
    this->day = dzien;
    this->priority = priorytet;
    this->note = notatka;
}

bool Task::saveToFile(const QString &sciezka) const
{
    QFile plik(sciezka);
    if (!plik.open(QIODevice::Append | QIODevice::Text))
        return false;

    QTextStream out(&plik);

    out << this->title << "|" << this->day << "|" << this->priority << "|" << this->note << "\n";


    plik.close();
    return true;
}

QString Task::getTitle() const
{
    return this->title;
}

QString Task::getDay() const
{
    return this->day;
}

int Task::getPriority() const
{
    return this->priority;
}

QString Task::getNote() const
{
    return this->note;
}

void Task::setTitle(const QString &tytul)
{
    this->title = tytul;
}

void Task::setDay(const QString &dzien)
{
    this->day = dzien;
}

void Task::setPriority(int priorytet)
{
    this->priority = priorytet;
}

void Task::setNote(const QString &notatka)
{
    this->note = notatka;
}
