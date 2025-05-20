#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Zadanie.h"

using namespace std;

void dodajZadanie() {
    int dzienInt, hStart, mStart, hEnd, mEnd, priorytet;
    string notatka;

    cout << "Wybierz dzien (0 - Poniedzialek, ..., 6 - Niedziela): ";
    cin >> dzienInt;

    cout << "Godzina rozpoczecia (0-23): ";
    cin >> hStart;
    cout << "Minuta rozpoczecia (0-59): ";
    cin >> mStart;
    cout << "Godzina zakonczenia (0-23): ";
    cin >> hEnd;
    cout << "Minuta zakonczenia (0-59): ";
    cin >> mEnd;

    cout << "Priorytet (liczba calkowita): ";
    cin >> priorytet;

    cout << "Notatka (bez znakow |): ";
    cin.ignore();
    getline(cin, notatka);

    Zadanie zad(static_cast<Zadanie::DzienTygodnia>(dzienInt), hStart, mStart, hEnd, mEnd, priorytet, notatka);


    ofstream plik("zadania.txt", ios::app);
    if (plik.is_open()) {
        plik << serializeZadanie(zad) << "\n";
        plik.close();
        cout << "Zadanie dodane.\n";
    }
    else {
        cout << "Blad zapisu do pliku.\n";
    }
}

void usunZadanie() {
    vector<Zadanie> zadania;
    ifstream plik("zadania.txt");
    string linia;

    if (!plik.is_open()) {
        cout << "Brak pliku z zadaniami.\n";
        return;
    }

    while (getline(plik, linia)) {
        if (!linia.empty())
            zadania.push_back(deserializeZadanie(linia));
    }
    plik.close();

    if (zadania.empty()) {
        cout << "Brak zadan do usuniecia.\n";
        return;
    }

    cout << "Lista zadan:\n";
    for (size_t i = 0; i < zadania.size(); i++) {
        cout << i << ": " << DzienTygodniaToString(zadania[i].getDzien()) << ", "
            << zadania[i].getHrozpoczecia() << ":" << zadania[i].getMinRozpoczecia() << " - "
            << zadania[i].getHZakonczenia() << ":" << zadania[i].getMinZakonczenia()
            << ", Priorytet: " << zadania[i].getPriorytet()
            << ", Notatka: " << zadania[i].getNotatka() << "\n";
    }

    cout << "Podaj numer zadania do usuniecia: ";
    int nr;
    cin >> nr;

    if (nr < 0 || nr >= (int)zadania.size()) {
        cout << "Niepoprawny numer.\n";
        return;
    }

    zadania.erase(zadania.begin() + nr);

    ofstream plikOut("zadania.txt", ios::trunc);
    if (plikOut.is_open()) {
        for (auto& zad : zadania) {
            plikOut << serializeZadanie(zad) << "\n";
        }
        plikOut.close();
        cout << "Zadanie usuniete.\n";
    }
    else {
        cout << "Blad zapisu do pliku.\n";
    }
}

int main() {
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Dodaj zadanie\n";
        cout << "2. Usun zadanie\n";
        cout << "3. Opusc planer\n";
        cout << "Wybor: ";

        int wybor;
        cin >> wybor;

        switch (wybor) {
        case 1:
            dodajZadanie();
            break;
        case 2:
            usunZadanie();
            break;
        case 3:
            cout << "Koniec programu.\n";
            return 0;
        default:
            cout << "Niepoprawny wybor.\n";
        }
    }
}
