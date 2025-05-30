#include "zadanie.h"
#include <QFile>
#include <QTextStream>

Task::Task()
    : priority(0)
{}

Task::Task(const QString &title, const QString &day, int priority, const QString &note)
{
    this->title = title;
    this->day = day;
    this->priority = priority;
    this->note = note;
}

bool Task::saveToFile(const QString &path) const
{
    QFile plik(path);
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

void Task::setTitle(const QString &title)
{
    this->title = title;
}

void Task::setDay(const QString &day)
{
    this->day = day;
}

void Task::setPriority(int priority)
{
    this->priority = priority;
}

void Task::setNote(const QString &note)
{
    this->note = note;
}
