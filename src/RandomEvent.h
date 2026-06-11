#ifndef RANDOM_EVENT_H
#define RANDOM_EVENT_H

#include <string>
#include <vector>
#include <memory>
#include "Game.h"
#include "Zdarzenia.h"

// stary enum zostawiony dla kompatybilnosci z Timer i GUI callback
enum TypZdarzenia {
    AFERA_BUDZIKOWA,
    PODEJRZENIA_ZENONA,
    PRZEWOD_JAKUBA,
    KLATWA_GRUPY_2,
    LAWKA_TROSKI
};

// klasa do losowania zdarzen z lore PP
// trzyma wektor unique_ptr do wszystkich zdarzen (klasa bazowa)
// kazde zdarzenie to pochodna klasa Zdarzenie czyli polimorfizm
class RandomEvent {
public:
    RandomEvent();

    // losuje zdarzenie i zwraca surowy wskaznik (wlasciciel zostaje w wektorze)
    Zdarzenie* losuj();

    // aplikuje skutki zdarzenia na obiekt gry (polimorficznie)
    void aplikuj(Game &g, Zdarzenie *z);

    // dla zgodnosci ze starym kodem
    TypZdarzenia losujZdarzenie();
    void aplikuj(Game &g, TypZdarzenia typ);
    std::string opisDlaUI(TypZdarzenia typ);

    // sprawdza czy zdarzenie jest klatwa (uzywa dynamic_cast)
    bool czyToKlatwa(Zdarzenie *z);

private:
    // jeden kontener trzymajacy wszystkie obiekty zdarzen
    // unique_ptr zeby zarzadzanie pamiecia bylo automatyczne
    std::vector<std::unique_ptr<Zdarzenie>> wszystkie;
};

#endif
