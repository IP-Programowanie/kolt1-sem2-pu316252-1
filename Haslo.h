#pragma once
#include <stdexcept>
#include <cstring>
#include <cctype>

class Haslo {
private:

    char haslo[13];

public:

    Haslo() = delete;

    Haslo(const char h[]) { setHaslo(h); }

    void setHaslo(const char* h) {

        int dlugosc = strlen(h);
        bool duza = false;
        bool mala = false;
        bool cyfra = false;

        if (dlugosc < 8 || dlugosc > 12) {

            throw std::invalid_argument("Niepoprawna dlugosc hasla!");
            return;
        }

        for (int i = 0; i < dlugosc; i++) {

            if (isupper(h[i])) duza = true;
            if (islower(h[i])) mala = true;
            if (isdigit(h[i])) cyfra = true;
        }

        if (duza && mala && cyfra) { strcpy(haslo, h); }
        else { throw std::invalid_argument("Brak malej litery, duzej litery lub cyfry"); }
    }

    const char* getHaslo() { return haslo; }
};
