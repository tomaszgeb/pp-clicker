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

    // logo PP - kolo zolte
    sf::CircleShape logo(100);
    logo.setPosition(300, 150);
    logo.setFillColor(sf::Color(200, 200, 50));
    okno.draw(logo);

    sf::Text txtLogo("PP", czcionka, 60);
    txtLogo.setPosition(370, 200);
    txtLogo.setFillColor(sf::Color::Black);
    okno.draw(txtLogo);

    // licznik punktow i ECTS
    char buf[256];
    snprintf(buf, sizeof(buf), "Punkty: %d", gra->getPunkty());
    sf::Text txtPunkty(buf, czcionka, 24);
    txtPunkty.setPosition(20, 20);
    txtPunkty.setFillColor(sf::Color::White);
    okno.draw(txtPunkty);

    snprintf(buf, sizeof(buf), "ECTS: %d / 210", gra->getEcts());
    sf::Text txtEcts(buf, czcionka, 24);
    txtEcts.setPosition(20, 50);
    txtEcts.setFillColor(sf::Color::White);
    okno.draw(txtEcts);

    snprintf(buf, sizeof(buf), "Dochod: %d/s", gra->getDochodPasywny());
    sf::Text txtDochod(buf, czcionka, 18);
    txtDochod.setPosition(20, 80);
    txtDochod.setFillColor(sf::Color(180, 180, 180));
    okno.draw(txtDochod);

    okno.display();
}