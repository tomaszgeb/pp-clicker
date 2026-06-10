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

        if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            int x = e.mouseButton.x;
            int y = e.mouseButton.y;

            // klikniecie w logo PP (kolo srodek 400,250 promien 100)
            int dx = x - 400;
            int dy = y - 250;
            if(dx*dx + dy*dy < 100*100) {
                gra->klik();
            }

            // klik w przyciski sklepu (z prawej, w pionie)
            for(int i = 0; i < sklep->liczbaItemow(); i++) {
                int yi = 50 + i * 80;
                if(x > 600 && x < 780 && y > yi && y < yi + 70) {
                    sklep->kup(i);//jak nie ma punktow to zwroci false ale nic sie nie stanie
                }
            }

            // klik w "kup ECTS" - lewy dolny rog
            if(x > 50 && x < 200 && y > 500 && y < 550) {
                gra->kupECTS();
            }
        }
    }
}

void GUI::rysuj() {
    okno.clear(sf::Color(30, 30, 40));

    // logo PP
    sf::CircleShape logo(100);
    logo.setPosition(300, 150);
    logo.setFillColor(sf::Color(200, 200, 50));
    okno.draw(logo);

    sf::Text txtLogo("PP", czcionka, 60);
    txtLogo.setPosition(370, 200);
    txtLogo.setFillColor(sf::Color::Black);
    okno.draw(txtLogo);

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

    // sklep z prawej strony
    for(int i = 0; i < sklep->liczbaItemow(); i++) {
        int yi = 50 + i * 80;
        sf::RectangleShape ramka(sf::Vector2f(180, 70));
        ramka.setPosition(600, yi);
        ramka.setFillColor(sf::Color(50, 50, 70));
        ramka.setOutlineThickness(2);
        ramka.setOutlineColor(sf::Color(100, 100, 120));
        okno.draw(ramka);

        ItemSklepu it = sklep->getItem(i);
        sf::Text txtNazwa(it.nazwa, czcionka, 18);
        txtNazwa.setPosition(610, yi + 5);
        txtNazwa.setFillColor(sf::Color::White);
        okno.draw(txtNazwa);

        snprintf(buf, sizeof(buf), "%d pkt (x%d)", sklep->aktualnaCena(i), it.ilePosiadanych);
        sf::Text txtCena(buf, czcionka, 14);
        txtCena.setPosition(610, yi + 30);
        txtCena.setFillColor(sf::Color(180, 180, 100));
        okno.draw(txtCena);
    }

    // przycisk kup ECTS
    sf::RectangleShape btnEcts(sf::Vector2f(150, 50));
    btnEcts.setPosition(50, 500);
    btnEcts.setFillColor(sf::Color(80, 120, 50));
    okno.draw(btnEcts);
    sf::Text txtBtn("Kup ECTS (1000)", czcionka, 16);
    txtBtn.setPosition(60, 515);
    txtBtn.setFillColor(sf::Color::White);
    okno.draw(txtBtn);

    // popup zdarzenia jak aktywny
    if(klatkiPopupu > 0) {
        sf::RectangleShape tlo(sf::Vector2f(600, 200));
        tlo.setPosition(100, 200);
        tlo.setFillColor(sf::Color(0, 0, 0, 220));
        tlo.setOutlineThickness(3);
        tlo.setOutlineColor(sf::Color::Red);
        okno.draw(tlo);

        sf::Text txt(aktualnyPopup, czcionka, 18);
        txt.setPosition(120, 220);
        txt.setFillColor(sf::Color::White);
        okno.draw(txt);

        klatkiPopupu--;
    }

    // ekran wygranej
    if(gra->czyWygrana()) {
        sf::Text wyg("WYGRANA! Zostales Inzynierem!", czcionka, 36);
        wyg.setPosition(120, 300);
        wyg.setFillColor(sf::Color::Yellow);
        okno.draw(wyg);
    }

    okno.display();
}
