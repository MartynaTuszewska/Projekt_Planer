#include "Zadanie.h"
#include <iostream>
#include <sstream> //to_string
using namespace std;

Zadanie::Zadanie(DzienTygodnia dzien, int h_rozpoczecia, int min_rozpoczecia, int h_zakonczenia, int min_zakonczenia, int priorytet, const std::string& notatka)
{
    this->dzien = dzien;
    this->h_rozpoczecia = h_rozpoczecia;
    this->min_rozpoczecia = min_rozpoczecia;
    this->h_zakonczenia = h_zakonczenia;
    this->min_zakonczenia = min_zakonczenia;
    this->priorytet = priorytet;
    this->notatka = notatka;
}


Zadanie::~Zadanie()
{
}

// Gettery
Zadanie::DzienTygodnia Zadanie::getDzien() const { return dzien; }
int Zadanie::getHrozpoczecia() const { return h_rozpoczecia; }
int Zadanie::getMinRozpoczecia() const { return min_rozpoczecia; }
int Zadanie::getHZakonczenia() const { return h_zakonczenia; }
int Zadanie::getMinZakonczenia() const { return min_zakonczenia; }
int Zadanie::getPriorytet() const { return priorytet; }
string Zadanie::getNotatka() const { return notatka; }

// Settery
void Zadanie::setDzien(DzienTygodnia dzien) { this->dzien = dzien; }
void Zadanie::setHrozpoczecia(int h) { this->h_rozpoczecia = h; }
void Zadanie::setMinRozpoczecia(int min) { this->min_rozpoczecia = min; }
void Zadanie::setHZakonczenia(int h) { this->h_zakonczenia = h; }
void Zadanie::setMinZakonczenia(int min) { this->min_zakonczenia = min; }
void Zadanie::setPriorytet(int priorytet) { this->priorytet = priorytet; }
void Zadanie::setNotatka(const string& notatka) { this->notatka = notatka; }

string serializeZadanie(const Zadanie& zad) {
    return DzienTygodniaToString(zad.getDzien()) + "|" +
        to_string(zad.getHrozpoczecia()) + "|" +
        to_string(zad.getMinRozpoczecia()) + "|" +
        to_string(zad.getHZakonczenia()) + "|" +
        to_string(zad.getMinZakonczenia()) + "|" +
        to_string(zad.getPriorytet()) + "|" +
        zad.getNotatka();
}

Zadanie deserializeZadanie(const string& linia) {
    stringstream ss(linia);
    string token;
    string pola[7];
    int i = 0;

    while (getline(ss, token, '|') && i < 7) {
        pola[i++] = token;
    }

    return Zadanie(
        StringToDzienTygodnia(pola[0]),
        stoi(pola[1]),
        stoi(pola[2]),
        stoi(pola[3]),
        stoi(pola[4]),
        stoi(pola[5]),
        pola[6]
    );
}
