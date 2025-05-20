#pragma once
#include <iostream>
#include <string>
#include <map>
using namespace std;

class Zadanie 
{
public:
    enum DzienTygodnia {
        Poniedzialek,
        Wtorek,
        Sroda,
        Czwartek,
        Piatek,
        Sobota,
        Niedziela
    };

    //Konstruktory i destruktory
    Zadanie(DzienTygodnia dzien, int h_rozpoczecia,int min_rozpoczecia,int h_zakonczenia,int min_zakonczenia,int priorytet,const string& notatka);
    ~Zadanie();

    // Gettery
    DzienTygodnia getDzien() const;
    int getHrozpoczecia() const;
    int getMinRozpoczecia() const;
    int getHZakonczenia() const;
    int getMinZakonczenia() const;
    int getPriorytet() const;
    string getNotatka() const;

    // Settery
    void setDzien(DzienTygodnia dzien);
    void setHrozpoczecia(int h);
    void setMinRozpoczecia(int min);
    void setHZakonczenia(int h);
    void setMinZakonczenia(int min);
    void setPriorytet(int priorytet);
    void setNotatka(const string& notatka);

private:
    DzienTygodnia dzien;
    int h_rozpoczecia;
    int min_rozpoczecia;
    int h_zakonczenia;
    int min_zakonczenia;
    int priorytet;
    string notatka;
};

inline string DzienTygodniaToString(Zadanie::DzienTygodnia dzien) {
    static map<Zadanie::DzienTygodnia, string> mapa = {
        {Zadanie::Poniedzialek, "Poniedzialek"},
        {Zadanie::Wtorek, "Wtorek"},
        {Zadanie::Sroda, "Sroda"},
        {Zadanie::Czwartek, "Czwartek"},
        {Zadanie::Piatek, "Piatek"},
        {Zadanie::Sobota, "Sobota"},
        {Zadanie::Niedziela, "Niedziela"}
    };
    return mapa[dzien];
}

inline Zadanie::DzienTygodnia StringToDzienTygodnia(const string& s) {
    static map<string, Zadanie::DzienTygodnia> mapa = {
        {"Poniedzialek", Zadanie::Poniedzialek},
        {"Wtorek", Zadanie::Wtorek},
        {"Sroda", Zadanie::Sroda},
        {"Czwartek", Zadanie::Czwartek},
        {"Piatek", Zadanie::Piatek},
        {"Sobota", Zadanie::Sobota},
        {"Niedziela", Zadanie::Niedziela}
    };
    return mapa[s];
}

string serializeZadanie(const Zadanie& zad);
Zadanie deserializeZadanie(const string& linia);
