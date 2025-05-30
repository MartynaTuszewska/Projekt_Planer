#ifndef ZADANIE_H
#define ZADANIE_H

#include <QString>

class Task
{
public:
    Task();
    Task(const QString &title, const QString &day, int priority, const QString &note);

    bool saveToFile(const QString &path) const;

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
