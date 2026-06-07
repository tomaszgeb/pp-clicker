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
    // pelne teksty z prezentacji - lore PP
    switch(typ) {
        case AFERA_BUDZIKOWA:
            return "AFERA BUDZIKOWA U ADAMA D.\n\n"
                   "Prowadzacy stwierdza: 'Nie kazdy musi byc\n"
                   "inzynierem, tym bardziej ci, co nie potrafia\n"
                   "wyciszyc budzika na egzaminie w sesji'.\n\n"
                   "KARA: Moc klikniecia spada o 50% na 30 sekund.";
        case PODEJRZENIA_ZENONA:
            return "PODEJRZENIA ZENONA Z.\n\n"
                   "'Mam co do Pana pewne podejrzenia'.\n\n"
                   "Na kazdym kolosie i egzaminie w sesji\n"
                   "gwarantowana pierwsza lawka.\n\n"
                   "KARA: Tracisz 35% punktow ECTS.";
        case PRZEWOD_JAKUBA:
            return "LATAJACY PRZEWOD JAKUBA K.\n\n"
                   "Zostales trafiony przewodem.\n\n"
                   "KARA: Tracisz 10% zgromadzonych punktow.";
        case KLATWA_GRUPY_2:
            return "KLATWA GRUPY NR 2\n\n"
                   "Macie zadanie z 15-minutowej wzmianki\n"
                   "z 6 wykladu. Zdaja 2 osoby z 30.\n"
                   "W tle slyszysz: 'To bylo banalnie proste,\n"
                   "jak ktos tego nie zrobil oznacza, ze od\n"
                   "pazdziernika nie uczyl sie nic!'\n\n"
                   "KARA: Dochod pasywny = 0 do poprawki.";
        case LAWKA_TROSKI:
            return "LAWKA SPECJALNEJ TROSKI\n\n"
                   "Zostales wybrany do tablicy na RRiPC.\n"
                   "Prowadzaca zapamietala cie jako gamonia.\n\n"
                   "KARA: Wszystkie przedmioty w sklepie\n"
                   "sa od teraz drozsze o 25%.";
    }
    return "";
}
