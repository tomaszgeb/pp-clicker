#include "Timer.h"
#include <chrono>
#include <cstdlib>

Timer::Timer(Game *g, RandomEvent *e) {
    gra = g;
    event = e;
    dziala = false;
    sekundyGry = 0;
    callback = nullptr;
}

Timer::~Timer() {
    stop();
}

void Timer::start() {
    dziala = true;
    watek = std::thread(&Timer::petla, this);
}

void Timer::stop() {
    dziala = false;
    if(watek.joinable()) watek.join();
}

void Timer::setEventCallback(CallbackZdarzenia fn) {
    callback = fn;
}

int Timer::getCzasGry() {
    return sekundyGry;
}

void Timer::petla() {
    int sekundyOdZdarzenia = 0;
    while(dziala) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if(!dziala) break;

        // co sekunde dochod pasywny + tick efektow czasowych
        gra->tickPasywny();
        gra->tickEfektyCzasowe();
        sekundyGry++;
        sekundyOdZdarzenia++;

        // co min 60s probujemy odpalic zdarzenie losowe (30% szans)
        if(sekundyOdZdarzenia >= 60) {
            if((rand() % 100) < 30) {
                TypZdarzenia t = event->losujZdarzenie();
                event->aplikuj(*gra, t);
                if(callback) {
                    callback(t, event->opisDlaUI(t));
                }
                sekundyOdZdarzenia = 0;
            }
        }
    }
}