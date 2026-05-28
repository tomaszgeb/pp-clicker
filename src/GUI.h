#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Game.h"
#include "Shop.h"

class GUI {
public:
    GUI(Game *g, Shop *s);

    void uruchom();// glowna petla

    void pokazPopupZdarzenia(const std::string &tekst);

private:
    Game *gra;
    Shop *sklep;
    sf::RenderWindow okno;
    sf::Font czcionka;

    std::string aktualnyPopup;
    int klatkiPopupu;//ile klatek ma byc widoczny

    void rysuj();
    void obsluzZdarzenia();
};

#endif