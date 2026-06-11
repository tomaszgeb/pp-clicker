#ifndef GAME_H
#define GAME_H

// klasa gry, tu siedzi caly stan
// punkty ECTS moc klika itp
// pola volatile bo Janek powiedzial ze inaczej dochod pasywny sie buguje
// (timer chodzi w osobnym watku i bez volatile wartosci sie nie odswiezaja)
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
    double getMnoznikCen();// 1.0 normalnie, wiecej po Lawce troski

    // settery do uzywania przez sklep Kuby i zdarzenia losowe
    void dodajPunkty(int ile);
    void odejmijPunkty(int ile);
    void odejmijEcts(int ile);
    void dodajMocKliku(int ile);
    void dodajDochodPasywny(int ile);
    void ustawMnoznikCen(double m);

    // do wczytywania stanu z bazy - Janek tego uzywa
    void ustawStan(int p, int e, int moc, int dochod);

    // efekty czasowe (afera budzikowa - 30s polowiczny klik)
    void aktywujEfektPolowicznegoKliku(int sekund);
    void tickEfektyCzasowe();// timer Janka wola co 1s

    // klatwa grupy 2 - dochod pasywny zerowany
    void aktywujKlatwe();
    void zdejmijKlatwe();
    bool czyKlatwa();

private:
    // volatile zeby kompilator nie cachowal wartosci miedzy watkami
    volatile int punkty;
    volatile int ects;
    volatile int mocKliku;//ile dodaje jeden klik domyslnie 1
    volatile int dochodPasywny;//ile dodaje sie co sekunde

    volatile int sekundyPolowicznegoKliku;//licznik afery budzikowej
    volatile bool klatwa;
    double mnoznikCen;//1.0 standard, modyfikowane tylko z GUI watku

    static const int CENA_ECTS = 1000;
    static const int CEL_ECTS = 210;
};

#endif
