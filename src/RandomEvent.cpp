#include "RandomEvent.h"
#include <cstdlib>
#include <ctime>

// w konstruktorze tworzymy 5 zdarzen przez make_unique
// kazde jest pochodna klasa, ale trzymamy je jako wskazniki do bazowej
// to pozwala na polimorfizm
RandomEvent::RandomEvent() {
    static bool zaseedowane = false;
    if(!zaseedowane) {
        srand((unsigned)time(0));
        zaseedowane = true;
    }

    // wektor wszystkich zdarzen, wszystkie obiekty w jednym kontenerze
    wszystkie.push_back(std::unique_ptr<Zdarzenie>(new AferaBudzikowa()));
    wszystkie.push_back(std::unique_ptr<Zdarzenie>(new PodejrzeniaZenona()));
    wszystkie.push_back(std::unique_ptr<Zdarzenie>(new PrzewodJakuba()));
    wszystkie.push_back(std::unique_ptr<Zdarzenie>(new KlatwaGrupy2()));
    wszystkie.push_back(std::unique_ptr<Zdarzenie>(new LawkaTroski()));
}

// losowanie konkretnego zdarzenia z wektora
Zdarzenie* RandomEvent::losuj() {
    int r = rand() % (int)wszystkie.size();
    return wszystkie[r].get();//zwracamy surowy wskaznik bez transferu ownership
}

// aplikuj polimorficznie, wywoluje virtual aplikuj() z pochodnej klasy
void RandomEvent::aplikuj(Game &g, Zdarzenie *z) {
    if(z) z->aplikuj(g);
}

// uzywa dynamic_cast zeby sprawdzic czy zdarzenie jest klatwa
// dynamic_cast zwraca nullptr jak typ nie pasuje
bool RandomEvent::czyToKlatwa(Zdarzenie *z) {
    KlatwaGrupy2 *k = dynamic_cast<KlatwaGrupy2*>(z);
    return k != nullptr;
}

// stara funkcja dla zgodnosci z Timer/GUI, mapuje na nowe klasy
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

// stara funkcja aplikowania po enumie, wewnetrznie szuka w wektorze
void RandomEvent::aplikuj(Game &g, TypZdarzenia typ) {
    if(typ >= 0 && typ < (int)wszystkie.size()) {
        wszystkie[typ]->aplikuj(g);
    }
}

// stara funkcja opisu, deleguje do nowej klasy przez wskaznik bazowy
std::string RandomEvent::opisDlaUI(TypZdarzenia typ) {
    if(typ >= 0 && typ < (int)wszystkie.size()) {
        return wszystkie[typ]->opis();
    }
    return "";
}
