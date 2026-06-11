#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Game.h"
#include "Shop.h"

// latajacy "+N" pojawiajacy sie przy klikach
struct LatajacyPlus {
    float x, y;
    int wartosc;
    int alpha;//przezroczystosc 255 do 0
};

class GUI {
public:
    GUI(Game *g, Shop *s);
    void uruchom();
    void pokazPopupZdarzenia(const std::string &tekst);

private:
    Game *gra;
    Shop *sklep;
    sf::RenderWindow okno;
    sf::Font czcionka;

    sf::Texture texLogo;
    sf::Sprite spriteLogo;
    std::vector<sf::Texture> texItemy;

    std::string aktualnyPopup;
    bool popupAktywny;//true jak trzeba kliknac OK zeby zniknal

    std::vector<LatajacyPlus> latajace;//efekty plus N od klikania

    void rysuj();
    void obsluzZdarzenia();
};

#endif
