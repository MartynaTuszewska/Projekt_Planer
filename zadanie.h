#ifndef ZADANIE_H
#define ZADANIE_H

#include <QString>

class Task
{
public:
    Task();
    Task(const QString &tytul, const QString &dzien, int priorytet, const QString &notatka);

    bool saveToFile(const QString &sciezka) const;

    QString getTitle() const;
    QString getDay() const;
    int getPriority() const;
    QString getNote() const;

    void setTitle(const QString &title);
    void setDay(const QString &day);
    void setPriority(int priority);
    void setNote(const QString &note);

private:
    QString title;
    QString day;
    int priority;
    QString note;
};

#endif
