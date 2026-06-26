#pragma once
#include <cassert>
#include "Uzytkownik.h"

class UzytkownikTymczasowy : public Uzytkownik
{
protected:
    using Uzytkownik::setHaslo;

private:
    int limitLogowan;

public:

    UzytkownikTymczasowy() = delete;
    UzytkownikTymczasowy(const UzytkownikTymczasowy&) = delete;
    UzytkownikTymczasowy(UzytkownikTymczasowy&&) = delete;
    UzytkownikTymczasowy& operator=(const UzytkownikTymczasowy&) = delete;
    UzytkownikTymczasowy& operator=(UzytkownikTymczasowy&&) = delete;

    UzytkownikTymczasowy(const Uzytkownik& u, int limit)
        : Uzytkownik(u.getNazwaUzytkownika(), u.getUprawnienia(), u.getCzasUzytkowania(), nullptr, u.getHaslo()->getHaslo())
    {
        if (limit < 0)
            throw std::invalid_argument("Limit logowan nie moze byc ujemny.");

        limitLogowan = limit;
    }

    virtual ~UzytkownikTymczasowy() override = default;

    void setLimitLogowan(int limit)
    {
        assert(limit >= 0);
        limitLogowan = limit;
    }

    bool zaloguj(const char* podaneHaslo) override
    {
        if (limitLogowan == 0)
            throw std::invalid_argument("Przekroczono limit logowan.");

        --limitLogowan;
        return Uzytkownik::zaloguj(podaneHaslo);
    }
};
