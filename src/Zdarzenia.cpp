#include "Zdarzenia.h"

// implementacje wszystkich 5 zdarzen
// kazde nadpisuje virtual funkcje z klasy bazowej Zdarzenie
// to jest polimorfizm w akcji

// AFERA BUDZIKOWA
void AferaBudzikowa::aplikuj(Game &g) {
    g.aktywujEfektPolowicznegoKliku(30);
}
std::string AferaBudzikowa::nazwa() const {
    return "Afera budzikowa u Adama D.";
}
std::string AferaBudzikowa::opis() const {
    return "AFERA BUDZIKOWA U ADAMA D.\n\n"
           "Prowadzacy stwierdza: 'Nie kazdy musi byc\n"
           "inzynierem, tym bardziej ci, co nie potrafia\n"
           "wyciszyc budzika na egzaminie w sesji'.\n\n"
           "KARA: Moc klikniecia spada o 50% na 30 sekund.";
}

// PODEJRZENIA ZENONA
void PodejrzeniaZenona::aplikuj(Game &g) {
    g.odejmijEcts((int)(g.getEcts() * 0.35));
}
std::string PodejrzeniaZenona::nazwa() const {
    return "Podejrzenia Zenona Z.";
}
std::string PodejrzeniaZenona::opis() const {
    return "PODEJRZENIA ZENONA Z.\n\n"
           "'Mam co do Pana pewne podejrzenia'.\n\n"
           "Na kazdym kolosie i egzaminie w sesji\n"
           "gwarantowana pierwsza lawka.\n\n"
           "KARA: Tracisz 35% punktow ECTS.";
}

// PRZEWOD JAKUBA
void PrzewodJakuba::aplikuj(Game &g) {
    g.odejmijPunkty((int)(g.getPunkty() * 0.10));
}
std::string PrzewodJakuba::nazwa() const {
    return "Latajacy przewod Jakuba K.";
}
std::string PrzewodJakuba::opis() const {
    return "LATAJACY PRZEWOD JAKUBA K.\n\n"
           "Zostales trafiony przewodem.\n\n"
           "KARA: Tracisz 10% zgromadzonych punktow.";
}

// KLATWA GRUPY 2
void KlatwaGrupy2::aplikuj(Game &g) {
    g.aktywujKlatwe();
}
std::string KlatwaGrupy2::nazwa() const {
    return "Klatwa Grupy nr 2";
}
std::string KlatwaGrupy2::opis() const {
    return "KLATWA GRUPY NR 2\n\n"
           "Macie zadanie z 15 minutowej wzmianki\n"
           "z 6 wykladu. Zdaja 2 osoby z 30.\n"
           "W tle slyszysz: 'To bylo banalnie proste,\n"
           "jak ktos tego nie zrobil oznacza, ze od\n"
           "pazdziernika nie uczyl sie nic!'\n\n"
           "KARA: Dochod pasywny = 0 do poprawki.";
}

// LAWKA TROSKI
void LawkaTroski::aplikuj(Game &g) {
    g.ustawMnoznikCen(g.getMnoznikCen() * 1.25);
}
std::string LawkaTroski::nazwa() const {
    return "Lawka specjalnej troski";
}
std::string LawkaTroski::opis() const {
    return "LAWKA SPECJALNEJ TROSKI\n\n"
           "Zostales wybrany do tablicy na RRiPC.\n"
           "Prowadzaca zapamietala cie jako gamonia.\n\n"
           "KARA: Wszystkie przedmioty w sklepie\n"
           "sa od teraz drozsze o 25%.";
}
