#ifndef GAME_H
#define GAME_H

// klasa gry - tu siedzi caly stan
// punkty ECTS moc klika itp
class Game {
public:
    Game();

    void klik();         // jeden klik dodaje punkty
    bool kupECTS();      // za 1000 pkt dostajesz 1 ECTS
    bool czyWygrana();   // ects >= 210 to wygrana

    int getPunkty();
    int getEcts();

private:
    int punkty;
    int ects;
    int mocKliku;//ile dodaje jeden klik domyslnie 1

    static const int CENA_ECTS = 1000;
    static const int CEL_ECTS = 210;
};

#endif
