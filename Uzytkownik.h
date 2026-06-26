#pragma once
#include <stdexcept>
#include "Haslo.h"

enum class Uprawnienia {

    Administracyjne = 0,
    Zwykle = 1
};

class Uzytkownik {
protected:

    char nazwaUzytkownika[21];
    Uprawnienia uprawnienia;
    double czasUzytkowania;
    Uzytkownik* wspolpracownik;
    Haslo* haslo;

    static double dopuszczalnyCzas[3];

private:

    void przypiszNazwe(const char* n) {

        if (n[0] >= '0' && n[0] <= '9') throw std::invalid_argument("Nazwa nie moze zaczynac sie od cyfry.");

        int i = 0;

        while (n[i] != '\0') {

            if (i >= 20) throw std::invalid_argument("Nazwa moze miec maksymalnie 20 znakow.");

            if (n[i] == ' ' || n[i] == '\t' || n[i] == '\n') {

                throw std::invalid_argument("Nazwa nie moze zawierac bialych znakow.");
            }

            nazwaUzytkownika[i] = n[i];
            i++;
        }

        nazwaUzytkownika[i] = '\0';
    }

public:

    Uzytkownik() = delete;
    Uzytkownik(const Uzytkownik&) = delete;
    Uzytkownik(Uzytkownik&&) = delete;
    Uzytkownik& operator=(const Uzytkownik&) = delete;
    Uzytkownik& operator=(Uzytkownik&&) = delete;

    Uzytkownik(const char* nazwa, Uprawnienia upr, double czas, Uzytkownik* wsp, const char* hasloStr)
        : uprawnienia(upr), wspolpracownik(wsp), haslo(nullptr), czasUzytkowania(0)
    {
        setUzytkownik(nazwa, upr, czas, wsp, hasloStr);
    }

    virtual ~Uzytkownik()
    {
        delete haslo;
    }

    void setUzytkownik(const char* nazwa, Uprawnienia upr, double czas, Uzytkownik* wsp, const char* h)
    {
        przypiszNazwe(nazwa);
        uprawnienia = upr;
        setCzasUzytkowania(czas);
        wspolpracownik = wsp;
        setHaslo(h);
    }

    const char* getNazwaUzytkownika() const;
    Uprawnienia getUprawnienia() const;
    Haslo* getHaslo() const;
    Uzytkownik* getWspolpracownik() const;
    double getCzasUzytkowania() const { return czasUzytkowania; }

    void setCzasUzytkowania(double czas) {

        bool ok = false;

        for (int i = 0; i < 3; i++) {

            if (czas == dopuszczalnyCzas[i]) {

                ok = true;
                break;
            }
        }

        if (!ok) throw std::invalid_argument("Niedozwolona wartosc czasu uzytkowania.");

        czasUzytkowania = czas;
    }

    void setHaslo(const char* h) {

        if (haslo == nullptr) haslo = new Haslo(h);
        else haslo->setHaslo(h);
    }

    virtual bool zaloguj(const char* podaneHaslo)
    {
        if (haslo == nullptr) return false;

        if (strcmp(haslo->getHaslo(), podaneHaslo) != 0) return false;

        if (uprawnienia == Uprawnienia::Zwykle)
        {
            double losowa = 1.0 + (rand() / (double)RAND_MAX) * 9.0;
            czasUzytkowania += losowa;
        }

        return true;
    }

    static void setDopuszczalnyCzas(const double nowa[3]) {

        for (int i = 0; i < 3; i++) {

            if (nowa[i] <= 0) throw std::invalid_argument("Dopuszczalne czasy musza byc dodatnie.");
            dopuszczalnyCzas[i] = nowa[i];
        }
    }

    void powiazZ(Uzytkownik* inne) {

        if (inne == nullptr) throw std::invalid_argument("Wskaznik nie moze byc pusty.");
        if (this == inne) throw std::invalid_argument("Wspolpracownik nie moze byc w asocjacji sam ze soba.");
        if (this->wspolpracownik != nullptr || inne->wspolpracownik != nullptr) {

            throw std::logic_error("Jeden z wspolpracownikow ma juz wspolpracownika.");
        }

        this->wspolpracownik = inne;
        inne->wspolpracownik = this;
    }
    void zerwijPowiazanie() {

        if (this->wspolpracownik != nullptr) {

            Uzytkownik* wsp = this->wspolpracownik;
            this->wspolpracownik = nullptr;
            wsp->wspolpracownik = nullptr;
        }
    }

};

double Uzytkownik::dopuszczalnyCzas[3] = { 10.0, 20.0, 50.0 };
