#include "Game.h"

// konstruktor - zerujemy wszystko, mocKliku startowa 1
Game::Game() {
    punkty = 0;
    ects = 0;
    mocKliku = 1;
}

// jeden klik = dodaj mocKliku punktow
void Game::klik() {
    punkty += mocKliku;
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
