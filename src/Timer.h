#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <atomic>
#include "Game.h"
#include "RandomEvent.h"

// timer w osobnym watku - co sekunde wola tickPasywny i tickEfektyCzasowe
class Timer {
public:
    Timer(Game *g, RandomEvent *e);
    ~Timer();

    void start();
    void stop();

    // callback do GUI - Kuba podepnie zeby pokazac popup
    typedef void (*CallbackZdarzenia)(TypZdarzenia, const std::string&);
    void setEventCallback(CallbackZdarzenia fn);

    int getCzasGry();// sekundy od startu - do rankingu

private:
    Game *gra;
    RandomEvent *event;
    std::thread watek;
    std::atomic<bool> dziala;
    std::atomic<int> sekundyGry;
    CallbackZdarzenia callback;

    void petla();
};

#endif