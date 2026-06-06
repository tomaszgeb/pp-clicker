#include "RandomEvent.h"
#include <cstdlib>
#include <ctime>

// seedujemy random tylko raz - flaga statyczna
RandomEvent::RandomEvent() {
    static bool zaseedowane = false;
    if(!zaseedowane) {
        srand((unsigned)time(0));
        zaseedowane = true;
    }
}

// losowanie - 5 mozliwosci rowne szanse
TypZdarzenia RandomEvent::losujZdarzenie() {
    int r = rand() % 5;
    switch(r) {
        case 0: return AFERA_BUDZIKOWA;
        case 1: return PODEJRZENIA_ZENONA;
        case 2: return PRZEWOD_JAKUBA;
        case 3: return KLATWA_GRUPY_2;
        default: return LAWKA_TROSKI;
    }
}

void RandomEvent::aplikuj(Game &g, TypZdarzenia typ) {
    switch(typ) {
        case AFERA_BUDZIKOWA:
            // moc klika polowa na 30 sekund
            g.aktywujEfektPolowicznegoKliku(30);
            break;
        case PODEJRZENIA_ZENONA:
            // tracisz 35% ECTS
            g.odejmijEcts((int)(g.getEcts() * 0.35));
            break;
        case PRZEWOD_JAKUBA:
            // -10% punktow
            g.odejmijPunkty((int)(g.getPunkty() * 0.10));
            break;
        case KLATWA_GRUPY_2:
            // dochod pasywny = 0 do poprawki
            g.aktywujKlatwe();
            break;
        case LAWKA_TROSKI:
            // sklep drozszy o 25%
            g.ustawMnoznikCen(g.getMnoznikCen() * 1.25);
            break;
    }
}

std::string RandomEvent::opisDlaUI(TypZdarzenia typ) {
    switch(typ) {
        case AFERA_BUDZIKOWA:
            return "Afera budzikowa u Adama D. Moc klika -50% na 30s.";
        case PODEJRZENIA_ZENONA:
            return "Podejrzenia Zenona Z. Tracisz 35% ECTS.";
        case PRZEWOD_JAKUBA:
            return "Latajacy przewod Jakuba K. Tracisz 10% punktow.";
        case KLATWA_GRUPY_2:
            return "Klatwa Grupy nr 2. Dochod pasywny = 0.";
        case LAWKA_TROSKI:
            return "Lawka specjalnej troski. Sklep drozszy.";
    }
    return "";
}
