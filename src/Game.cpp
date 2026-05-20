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

int Game::getPunkty() {
    return punkty;
}

int Game::getEcts() {
    return ects;
}
