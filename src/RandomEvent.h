#ifndef RANDOM_EVENT_H
#define RANDOM_EVENT_H

#include <string>
#include "Game.h"

// typy zdarzen losowych z prezentacji - 5 rodzajow
enum TypZdarzenia {
    AFERA_BUDZIKOWA,    // moc klika -50% na 30s (Adam D.)
    PODEJRZENIA_ZENONA, // -35% ECTS (Zenon Z.)
    PRZEWOD_JAKUBA,     // -10% punktow (Jakub K.)
    KLATWA_GRUPY_2,     // dochod pasywny = 0 (grupa nr 2)
    LAWKA_TROSKI        // sklep drozszy (RRiPC)
};

class RandomEvent {
public:
    RandomEvent();

    // losuje jakies zdarzenie i zwraca typ
    TypZdarzenia losujZdarzenie();

    // aplikuje skutki - modyfikuje stan gry
    void aplikuj(Game &g, TypZdarzenia typ);

    // tekst dla popupu (Kuba uzyje w GUI)
    std::string opisDlaUI(TypZdarzenia typ);
};

#endif
