#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <vector>
#include "Game.h"

// jeden item ze sklepu (z prezentacji)
struct ItemSklepu {
    std::string nazwa;
    std::string opis;//krotki opis co item robi
    int bazowaCena;
    int dodajMocyKliku;
    int dodajDochoduPasywnego;
    int ilePosiadanych;//ile juz kupiles, cena rosnie z kazdym
};

class Shop {
public:
    Shop(Game *g);

    int liczbaItemow();
    ItemSklepu getItem(int idx);

    // aktualna cena z uwzglednieniem mnoznika z Lawki troski
    // dodatkowo cena rosnie x1.15 za kazda kupiona sztuke
    int aktualnaCena(int idx);

    bool kup(int idx);

    // do wczytania z bazy, ustawia ile gracz mial kupione kazdego itemu
    void ustawIloscPosiadanych(int idx, int ile);

private:
    Game *gra;
    std::vector<ItemSklepu> itemy;
};

#endif