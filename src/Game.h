#ifndef GAME_H
#define GAME_H

// klasa gry - tu siedzi caly stan
// punkty ECTS moc klika itp
class Game {
public:
    Game();

    void klik();         // jeden klik dodaje punkty
    void tickPasywny();  // co sekunde wola to timer Janka - dochod pasywny
    bool kupECTS();      // za 1000 pkt dostajesz 1 ECTS
    bool czyWygrana();   // ects >= 210 to wygrana

    int getPunkty();
    int getEcts();
    int getDochodPasywny();
    int getMocKliku();

    // settery do uzywania przez sklep Kuby i zdarzenia losowe
    void dodajPunkty(int ile);
    void odejmijPunkty(int ile);
    void dodajMocKliku(int ile);
    void dodajDochodPasywny(int ile);

private:
    int punkty;
    int ects;
    int mocKliku;//ile dodaje jeden klik domyslnie 1
    int dochodPasywny;//ile dodaje sie co sekunde

    static const int CENA_ECTS = 1000;
    static const int CEL_ECTS = 210;
};

#endif
