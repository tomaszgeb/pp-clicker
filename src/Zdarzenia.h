#ifndef ZDARZENIA_H
#define ZDARZENIA_H

#include <string>
#include "Game.h"

// klasa bazowa abstrakcyjna dla wszystkich zdarzen losowych
// kazde zdarzenie dziedziczy po niej i nadpisuje aplikuj() i opis()
// to nam daje polimorfizm, mozemy trzymac wskazniki do roznych klas
// w jednym wektorze i wywolywac aplikuj() bez wiedzy co to za zdarzenie
class Zdarzenie {
public:
    virtual ~Zdarzenie() {}//wirtualny destruktor zeby przy delete na bazowej
                           //wywolal sie destruktor pochodnej

    // czysto wirtualna, kazda pochodna musi to nadpisac
    virtual void aplikuj(Game &g) = 0;
    virtual std::string opis() const = 0;
    virtual std::string nazwa() const = 0;
};

// 1. Afera budzikowa Adama D., moc klika minus 50% na 30 sekund
class AferaBudzikowa : public Zdarzenie {
public:
    void aplikuj(Game &g) override;
    std::string opis() const override;
    std::string nazwa() const override;
};

// 2. Podejrzenia Zenona Z., minus 35% ECTS
class PodejrzeniaZenona : public Zdarzenie {
public:
    void aplikuj(Game &g) override;
    std::string opis() const override;
    std::string nazwa() const override;
};

// 3. Latajacy przewod Jakuba K., minus 10% punktow
class PrzewodJakuba : public Zdarzenie {
public:
    void aplikuj(Game &g) override;
    std::string opis() const override;
    std::string nazwa() const override;
};

// 4. Klatwa Grupy nr 2, dochod pasywny zerowany
class KlatwaGrupy2 : public Zdarzenie {
public:
    void aplikuj(Game &g) override;
    std::string opis() const override;
    std::string nazwa() const override;
};

// 5. Lawka specjalnej troski, sklep drozszy o 25%
class LawkaTroski : public Zdarzenie {
public:
    void aplikuj(Game &g) override;
    std::string opis() const override;
    std::string nazwa() const override;
};

#endif
