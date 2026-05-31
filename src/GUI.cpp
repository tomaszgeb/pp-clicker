#include "GUI.h"
#include <iostream>
#include <cstdio>

GUI::GUI(Game *g, Shop *s) {
    gra = g;
    sklep = s;

    okno.create(sf::VideoMode(800, 600), "PP Clicker - Droga do Inzyniera");
    okno.setFramerateLimit(60);

    if(!czcionka.loadFromFile("assets/arial.ttf")) {
        std::cerr << "brak czcionki - dodaj plik assets/arial.ttf" << std::endl;
    }

    klatkiPopupu = 0;
}

void GUI::uruchom() {
    while(okno.isOpen()) {
        obsluzZdarzenia();
        rysuj();
    }
}

void GUI::pokazPopupZdarzenia(const std::string &tekst) {
    aktualnyPopup = tekst;
    klatkiPopupu = 5 * 60;//5 sekund * 60fps
}

void GUI::obsluzZdarzenia() {
    sf::Event e;
    while(okno.pollEvent(e)) {
        if(e.type == sf::Event::Closed) okno.close();
    }
}

void GUI::rysuj() {
    okno.clear(sf::Color(30, 30, 40));
    okno.display();
}