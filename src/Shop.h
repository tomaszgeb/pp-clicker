#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <vector>
#include "Game.h"

// jeden item ze sklepu (z prezentacji)
struct ItemSklepu {
    std::string nazwa;
    int bazowaCena;
    int dodajMocyKliku;
    int dodajDochoduPasywnego;
    int ilePosiadanych;//ile juz kupiles - cena rosnie z kazdym
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

private:
    Game *gra;
    std::vector<ItemSklepu> itemy;
};

#endif