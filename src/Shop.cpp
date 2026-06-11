#include "Shop.h"
#include <cmath>

Shop::Shop(Game *g) {
    gra = g;

    // itemy z prezentacji, 4 sztuki, kazdy ma swoj opis lore PP

    ItemSklepu i1;
    i1.nazwa = "Kawa";
    i1.opis = "Stawia na nogi na porannym wykladzie";
    i1.bazowaCena = 500;
    i1.dodajMocyKliku = 1;
    i1.dodajDochoduPasywnego = 0;
    i1.ilePosiadanych = 0;
    itemy.push_back(i1);

    ItemSklepu i2;
    i2.nazwa = "Baza Kolosow";
    i2.opis = "Baza kolokwiow z poprzednich lat. Szansa 50% ze bedzie twoj prowadzacy";
    i2.bazowaCena = 1500;
    i2.dodajMocyKliku = 0;
    i2.dodajDochoduPasywnego = 5;
    i2.ilePosiadanych = 0;
    itemy.push_back(i2);

    ItemSklepu i3;
    i3.nazwa = "Kolega";
    i3.opis = "Zawsze wpisze cie na liste obecnosci";
    i3.bazowaCena = 8000;
    i3.dodajMocyKliku = 0;
    i3.dodajDochoduPasywnego = 25;
    i3.ilePosiadanych = 0;
    itemy.push_back(i3);

    ItemSklepu i4;
    i4.nazwa = "Gemini Pro";
    i4.opis = "Absolutny game changer. Darmowy dla studentow lecz przespales promocje";
    i4.bazowaCena = 18000;
    i4.dodajMocyKliku = 10;
    i4.dodajDochoduPasywnego = 50;
    i4.ilePosiadanych = 0;
    itemy.push_back(i4);
}

int Shop::liczbaItemow() {
    return (int)itemy.size();
}

ItemSklepu Shop::getItem(int idx) {
    return itemy[idx];
}

int Shop::aktualnaCena(int idx) {
    ItemSklepu &it = itemy[idx];
    // cena = bazowa * 1.15^ilePosiadanych * mnoznikCen
    double cena = it.bazowaCena * pow(1.15, it.ilePosiadanych);
    cena *= gra->getMnoznikCen();//mnoznik z Lawki troski
    return (int)cena;
}

// ustawia ile_posiadanych dla itemu (uzywane przy wczytaniu z bazy)
void Shop::ustawIloscPosiadanych(int idx, int ile) {
    if(idx < 0 || idx >= (int)itemy.size()) return;
    itemy[idx].ilePosiadanych = ile;
}

bool Shop::kup(int idx) {
    if(idx < 0 || idx >= (int)itemy.size()) return false;

    int cena = aktualnaCena(idx);
    if(gra->getPunkty() < cena) return false;//brak punktow

    gra->odejmijPunkty(cena);
    ItemSklepu &it = itemy[idx];
    gra->dodajMocKliku(it.dodajMocyKliku);
    gra->dodajDochodPasywny(it.dodajDochoduPasywnego);
    it.ilePosiadanych++;
    return true;
}