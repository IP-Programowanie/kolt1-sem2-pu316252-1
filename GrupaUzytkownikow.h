#pragma once
#include "Uzytkownik.h"

class GrupaUzytkownikow {
private:

    static const short MAKS_LUDZI = 30;
    Uzytkownik* ludzie[MAKS_LUDZI];
    short liczbaLudzi = 0;

public:

    void dodajUzytkownika(Uzytkownik& u) {

        for (int i = 0; i < liczbaLudzi; i++)
            if (ludzie[i] == &u) return;

        if (liczbaLudzi < MAKS_LUDZI) ludzie[liczbaLudzi++] = &u;
    }
};
