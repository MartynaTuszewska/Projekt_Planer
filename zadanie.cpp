#include "zadanie.h"
#include <QFile>
#include <QTextStream>

Zadanie::Zadanie()
    : priorytet(0)
{}

Zadanie::Zadanie(const QString &tytul, const QString &dzien, int priorytet, const QString &notatka)
{
    this->tytul = tytul;
    this->dzien = dzien;
    this->priorytet = priorytet;
    this->notatka = notatka;
}

bool Zadanie::zapiszDoPliku(const QString &sciezka) const
{
    QFile plik(sciezka);
    if (!plik.open(QIODevice::Append | QIODevice::Text))
        return false;

    QTextStream out(&plik);

    out << this->tytul << "|" << this->dzien << "|" << this->priorytet << "|" << this->notatka << "\n";


    plik.close();
    return true;
}

QString Zadanie::getTytul() const
{
    return this->tytul;
}

QString Zadanie::getDzien() const
{
    return this->dzien;
}

int Zadanie::getPriorytet() const
{
    return this->priorytet;
}

QString Zadanie::getNotatka() const
{
    return this->notatka;
}

void Zadanie::setTytul(const QString &tytul)
{
    this->tytul = tytul;
}

void Zadanie::setDzien(const QString &dzien)
{
    this->dzien = dzien;
}

void Zadanie::setPriorytet(int priorytet)
{
    this->priorytet = priorytet;
}

void Zadanie::setNotatka(const QString &notatka)
{
    this->notatka = notatka;
}
