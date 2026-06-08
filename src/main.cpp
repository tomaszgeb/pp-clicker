#include <iostream>
#include "Game.h"

// testowy main - sprawdzam czy silnik dziala
// docelowo Kuba podlaczy GUI na to
int main() {
    std::cout << "PP Clicker - test silnika" << std::endl;

    Game g;
    // 1500 klikow zeby kupic 1 ECTS i miec 500 pkt zapasu
    for(int i = 0; i < 1500; i++) {
        g.klik();
    }
    std::cout << "Po 1500 klikow:" << std::endl;
    std::cout << "  punkty: " << g.getPunkty() << std::endl;

    if(g.kupECTS()) {
        std::cout << "Kupilem 1 ECTS" << std::endl;
    }
    std::cout << "  punkty po zakupie: " << g.getPunkty() << std::endl;
    std::cout << "  ects: " << g.getEcts() << std::endl;
    std::cout << "  wygrana? " << (g.czyWygrana() ? "tak" : "nie") << std::endl;

    return 0;
}
