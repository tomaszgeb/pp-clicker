#include "Game.h"

// konstruktor - zerujemy wszystko, mocKliku startowa 1
Game::Game() {
    punkty = 0;
    ects = 0;
    mocKliku = 1;
    dochodPasywny = 0;
    sekundyPolowicznegoKliku = 0;
    klatwa = false;
}

// jeden klik = dodaj mocKliku punktow
// jezeli afera budzikowa aktywna to polowiczne
void Game::klik() {
    if(sekundyPolowicznegoKliku > 0) {
        punkty += mocKliku / 2;//div calkowite - jak 1 to 0 trudno
    } else {
        punkty += mocKliku;
    }
}

// dochod pasywny - co 1s timer to wola
// timer pisze Janek u siebie w Timer.cpp
// klatwa zeruje dochod
void Game::tickPasywny() {
    if(klatwa) return;
    punkty += dochodPasywny;
}

// kupowanie ECTS za punkty - za 1000 pkt 1 ECTS
bool Game::kupECTS() {
    if(punkty < CENA_ECTS) return false;
    punkty -= CENA_ECTS;
    ects = ects + 1;
    return true;
}

// wygrana = uzbieralo sie 210 ECTS
bool Game::czyWygrana() {
    return ects >= CEL_ECTS;
}

int Game::getPunkty() {
    return punkty;
}

int Game::getEcts() {
    return ects;
}

int Game::getDochodPasywny() {
    return dochodPasywny;
}

int Game::getMocKliku() {
    return mocKliku;
}

// settery - sklep i zdarzenia losowe ich uzywaja
void Game::dodajPunkty(int ile) {
    punkty += ile;
}

void Game::odejmijPunkty(int ile) {
    punkty -= ile;
    if(punkty < 0) punkty = 0;//nie chcemy ujemnych punktow
}

void Game::dodajMocKliku(int ile) {
    mocKliku += ile;
}

void Game::dodajDochodPasywny(int ile) {
    dochodPasywny += ile;
}

// odejmowanie ECTS - Zenon zabiera 35%
void Game::odejmijEcts(int ile) {
    ects -= ile;
    if(ects < 0) ects = 0;
}

// afera budzikowa - aktywuj efekt na X sekund
void Game::aktywujEfektPolowicznegoKliku(int sekund) {
    sekundyPolowicznegoKliku = sekund;
}

// timer Janka co 1s wola - odejmujemy sekunde od efektu
void Game::tickEfektyCzasowe() {
    if(sekundyPolowicznegoKliku > 0) {
        sekundyPolowicznegoKliku--;
    }
}

void Game::aktywujKlatwe() {
    klatwa = true;
}

void Game::zdejmijKlatwe() {
    klatwa = false;
}

bool Game::czyKlatwa() {
    return klatwa;
}
