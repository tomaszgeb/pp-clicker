#include "Game.h"

// konstruktor - zerujemy wszystko, mocKliku startowa 1
Game::Game() {
    punkty = 0;
    ects = 0;
    mocKliku = 1;
    dochodPasywny = 0;
}

// jeden klik = dodaj mocKliku punktow
void Game::klik() {
    punkty += mocKliku;
}

// dochod pasywny - co 1s timer to wola
// timer pisze Janek u siebie w Timer.cpp
void Game::tickPasywny() {
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
