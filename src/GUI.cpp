#include "GUI.h"
#include <iostream>
#include <cstdio>

GUI::GUI(Game *g, Shop *s) {
    gra = g;
    sklep = s;

    okno.create(sf::VideoMode(900, 700), "PP Clicker. Droga do Inzyniera");
    okno.setFramerateLimit(60);

    if(!czcionka.loadFromFile("assets/arial.ttf")) {
        std::cerr << "brak czcionki, dodaj assets/arial.ttf" << std::endl;
    }

    if(!texLogo.loadFromFile("assets/logo_pp.png")) {
        std::cerr << "brak assets/logo_pp.png" << std::endl;
    }
    texLogo.setSmooth(true);
    spriteLogo.setTexture(texLogo);
    float skala = 280.0f / texLogo.getSize().x;
    spriteLogo.setScale(skala, skala);
    spriteLogo.setPosition(180, 200);

    const char* pliki[] = {"assets/kawa.png", "assets/baza.png", "assets/kolega.png", "assets/gemini.png"};
    texItemy.resize(4);
    for(int i = 0; i < 4; i++) {
        if(!texItemy[i].loadFromFile(pliki[i])) {
            std::cerr << "brak " << pliki[i] << std::endl;
        }
        texItemy[i].setSmooth(true);
    }

    popupAktywny = false;
}

void GUI::uruchom() {
    while(okno.isOpen()) {
        obsluzZdarzenia();
        rysuj();
    }
}

void GUI::pokazPopupZdarzenia(const std::string &tekst) {
    aktualnyPopup = tekst;
    popupAktywny = true;
}

void GUI::obsluzZdarzenia() {
    sf::Event e;
    while(okno.pollEvent(e)) {
        if(e.type == sf::Event::Closed) okno.close();

        if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            int x = e.mouseButton.x;
            int y = e.mouseButton.y;

            // popup aktywny, sprawdz tylko OK button, reszte ignoruj
            if(popupAktywny) {
                if(x > 410 && x < 490 && y > 530 && y < 570) {
                    popupAktywny = false;
                }
                continue;
            }

            // klik w logo PP, srodek (320, 340) promien 140
            int dx = x - 320;
            int dy = y - 340;
            if(dx*dx + dy*dy < 140*140) {
                gra->klik();
                LatajacyPlus lp;
                lp.x = (float)x;
                lp.y = (float)y;
                lp.wartosc = gra->getMocKliku();
                lp.alpha = 255;
                latajace.push_back(lp);
            }

            // klik w sklep z prawej
            for(int i = 0; i < sklep->liczbaItemow(); i++) {
                int yi = 50 + i * 150;
                if(x > 600 && x < 870 && y > yi && y < yi + 140) {
                    sklep->kup(i);
                }
            }

            // klik kup ECTS na dole
            if(x > 60 && x < 280 && y > 620 && y < 680) {
                gra->kupECTS();
            }
        }
    }
}

void GUI::rysuj() {
    okno.clear(sf::Color(25, 28, 38));

    okno.draw(spriteLogo);

    char buf[256];
    snprintf(buf, sizeof(buf), "Punkty: %d", gra->getPunkty());
    sf::Text txtPunkty(buf, czcionka, 26);
    txtPunkty.setPosition(20, 20);
    txtPunkty.setFillColor(sf::Color::White);
    okno.draw(txtPunkty);

    snprintf(buf, sizeof(buf), "ECTS: %d / 210", gra->getEcts());
    sf::Text txtEcts(buf, czcionka, 26);
    txtEcts.setPosition(20, 55);
    txtEcts.setFillColor(sf::Color(255, 200, 80));
    okno.draw(txtEcts);

    snprintf(buf, sizeof(buf), "Moc/klik: %d", gra->getMocKliku());
    sf::Text txtMoc(buf, czcionka, 18);
    txtMoc.setPosition(20, 95);
    txtMoc.setFillColor(sf::Color(180, 200, 220));
    okno.draw(txtMoc);

    snprintf(buf, sizeof(buf), "Dochod: %d/s", gra->getDochodPasywny());
    sf::Text txtDochod(buf, czcionka, 18);
    txtDochod.setPosition(20, 120);
    txtDochod.setFillColor(sf::Color(180, 200, 220));
    okno.draw(txtDochod);

    if(gra->czyKlatwa()) {
        sf::Text txtKlatwa("Klatwa Grupy 2 aktywna", czcionka, 14);
        txtKlatwa.setPosition(20, 145);
        txtKlatwa.setFillColor(sf::Color::Red);
        okno.draw(txtKlatwa);
    }

    // sklep z prawej, ramka 270x140 z ikonka, nazwa, opisem, cena
    for(int i = 0; i < sklep->liczbaItemow(); i++) {
        int yi = 50 + i * 150;
        sf::RectangleShape ramka(sf::Vector2f(270, 140));
        ramka.setPosition(600, yi);
        ramka.setFillColor(sf::Color(45, 48, 60));
        ramka.setOutlineThickness(2);
        ramka.setOutlineColor(sf::Color(90, 95, 110));
        okno.draw(ramka);

        sf::Sprite ikona(texItemy[i]);
        float sk = 90.0f / texItemy[i].getSize().x;
        ikona.setScale(sk, sk);
        ikona.setPosition(608, yi + 25);
        okno.draw(ikona);

        ItemSklepu it = sklep->getItem(i);

        sf::Text txtNazwa(it.nazwa, czcionka, 16);
        txtNazwa.setPosition(708, yi + 8);
        txtNazwa.setStyle(sf::Text::Bold);
        txtNazwa.setFillColor(sf::Color::White);
        okno.draw(txtNazwa);

        // opis itemu, lamiemy linie zeby zmiescic w ramce
        std::string opis = it.opis;
        size_t spl = 0;
        const size_t MAX_CHARS = 22;
        int linia = 0;
        while(spl < opis.size() && linia < 3) {
            size_t koniec = spl + MAX_CHARS;
            if(koniec >= opis.size()) {
                koniec = opis.size();
            } else {
                // szukamy ostatniej spacji aby nie lamac slowa
                size_t spacja = opis.rfind(' ', koniec);
                if(spacja != std::string::npos && spacja > spl) koniec = spacja;
            }
            std::string fragment = opis.substr(spl, koniec - spl);
            sf::Text txtOpis(fragment, czcionka, 11);
            txtOpis.setPosition(708, yi + 30 + linia * 14);
            txtOpis.setFillColor(sf::Color(200, 200, 210));
            okno.draw(txtOpis);
            spl = koniec;
            if(spl < opis.size() && opis[spl] == ' ') spl++;
            linia++;
        }

        snprintf(buf, sizeof(buf), "%d pkt", sklep->aktualnaCena(i));
        sf::Text txtCena(buf, czcionka, 14);
        txtCena.setPosition(708, yi + 90);
        txtCena.setFillColor(sf::Color(255, 220, 100));
        okno.draw(txtCena);

        snprintf(buf, sizeof(buf), "masz: %d", it.ilePosiadanych);
        sf::Text txtIlosc(buf, czcionka, 12);
        txtIlosc.setPosition(708, yi + 112);
        txtIlosc.setFillColor(sf::Color(160, 160, 160));
        okno.draw(txtIlosc);
    }

    // przycisk kup ECTS
    sf::RectangleShape btnEcts(sf::Vector2f(220, 60));
    btnEcts.setPosition(60, 620);
    btnEcts.setFillColor(sf::Color(70, 130, 60));
    btnEcts.setOutlineThickness(2);
    btnEcts.setOutlineColor(sf::Color(120, 180, 100));
    okno.draw(btnEcts);

    sf::Text txtBtn("Kup ECTS (1000 pkt)", czcionka, 18);
    txtBtn.setPosition(80, 638);
    txtBtn.setFillColor(sf::Color::White);
    okno.draw(txtBtn);

    // latajace plus N z mini moneta obok, aktualizuj i rysuj
    for(size_t i = 0; i < latajace.size(); ) {
        LatajacyPlus &lp = latajace[i];
        lp.y -= 1.4f;//w gore troche szybciej
        lp.alpha -= 4;
        if(lp.alpha <= 0) {
            latajace.erase(latajace.begin() + i);
            continue;
        }
        sf::Uint8 a = (sf::Uint8)lp.alpha;

        // tekst "+N" zielony bo to przyrost
        char bb[32];
        snprintf(bb, sizeof(bb), "+%d", lp.wartosc);
        sf::Text txt(bb, czcionka, 26);
        txt.setPosition(lp.x, lp.y);
        txt.setStyle(sf::Text::Bold);
        txt.setFillColor(sf::Color(120, 230, 120, a));
        okno.draw(txt);

        // mini moneta obok cyfry
        sf::CircleShape moneta(8);
        moneta.setPosition(lp.x + 40, lp.y + 8);
        moneta.setFillColor(sf::Color(255, 215, 0, a));
        moneta.setOutlineThickness(1);
        moneta.setOutlineColor(sf::Color(180, 140, 0, a));
        okno.draw(moneta);

        i++;
    }

    // popup zdarzenia z przyciskiem OK
    if(popupAktywny) {
        sf::RectangleShape przyciemnienie(sf::Vector2f(900, 700));
        przyciemnienie.setFillColor(sf::Color(0, 0, 0, 140));
        okno.draw(przyciemnienie);

        sf::RectangleShape panel(sf::Vector2f(500, 360));
        panel.setPosition(200, 170);
        panel.setFillColor(sf::Color(35, 38, 50));
        panel.setOutlineThickness(3);
        panel.setOutlineColor(sf::Color(220, 60, 60));
        okno.draw(panel);

        sf::Text naglowek("! ZDARZENIE LOSOWE !", czcionka, 18);
        naglowek.setPosition(290, 180);
        naglowek.setStyle(sf::Text::Bold);
        naglowek.setFillColor(sf::Color(255, 100, 100));
        okno.draw(naglowek);

        sf::Text txt(aktualnyPopup, czcionka, 13);
        txt.setPosition(220, 215);
        txt.setFillColor(sf::Color::White);
        okno.draw(txt);

        // komunikat ze trzeba kliknac OK
        sf::Text txtKlik("Kliknij OK aby kontynuowac. Gra jest zablokowana", czcionka, 11);
        txtKlik.setPosition(220, 500);
        txtKlik.setFillColor(sf::Color(180, 180, 180));
        okno.draw(txtKlik);

        // przycisk OK
        sf::RectangleShape btnOk(sf::Vector2f(80, 40));
        btnOk.setPosition(410, 530);
        btnOk.setFillColor(sf::Color(120, 60, 60));
        btnOk.setOutlineThickness(2);
        btnOk.setOutlineColor(sf::Color(200, 100, 100));
        okno.draw(btnOk);

        sf::Text txtOk("OK", czcionka, 20);
        txtOk.setPosition(434, 535);
        txtOk.setStyle(sf::Text::Bold);
        txtOk.setFillColor(sf::Color::White);
        okno.draw(txtOk);
    }

    if(gra->czyWygrana()) {
        sf::RectangleShape tlo(sf::Vector2f(900, 200));
        tlo.setPosition(0, 250);
        tlo.setFillColor(sf::Color(0, 0, 0, 220));
        okno.draw(tlo);

        sf::Text wyg("WYGRANA. Zostales Inzynierem!", czcionka, 36);
        wyg.setPosition(170, 300);
        wyg.setFillColor(sf::Color::Yellow);
        wyg.setStyle(sf::Text::Bold);
        okno.draw(wyg);
    }

    okno.display();
}
