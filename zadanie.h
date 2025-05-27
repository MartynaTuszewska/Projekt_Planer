#ifndef ZADANIE_H
#define ZADANIE_H

#include <QString>

class Zadanie
{
public:
    Zadanie();
    Zadanie(const QString &tytul, const QString &dzien, int priorytet, const QString &notatka);

    bool zapiszDoPliku(const QString &sciezka) const;

    QString getTytul() const;
    QString getDzien() const;
    int getPriorytet() const;
    QString getNotatka() const;

    void setTytul(const QString &tytul);
    void setDzien(const QString &dzien);
    void setPriorytet(int priorytet);
    void setNotatka(const QString &notatka);

private:
    QString tytul;
    QString dzien;
    int priorytet;
    QString notatka;
};

#endif
