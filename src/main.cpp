#include <iostream>
#include "Game.h"
#include "Shop.h"
#include "GUI.h"
#include "Database.h"
#include "Timer.h"
#include "RandomEvent.h"

// globalny wskaznik do GUI - do callbacka zdarzen losowych
GUI *gGui = nullptr;

void onZdarzenie(TypZdarzenia typ, const std::string &opis) {
    (void)typ;
    if(gGui) gGui->pokazPopupZdarzenia(opis);
}

int main() {
    Game gra;
    Shop sklep(&gra);
    RandomEvent event;
    Database baza("pp-clicker.db");
    Timer timer(&gra, &event);

    baza.init();
    baza.wczytajStanGry(gra);

    GUI gui(&gra, &sklep);
    gGui = &gui;
    timer.setEventCallback(onZdarzenie);
    timer.start();

    gui.uruchom();

    timer.stop();
    baza.zapiszStanGry(gra);
    return 0;
}
