#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include "Game.h"

// jeden wpis w rankingu (do leaderboard)
struct WpisRankingu {
    std::string nick;
    int sekundy;//czas ukonczenia w sekundach
};

class Database {
public:
    Database(const std::string &plik);
    ~Database();

    bool init();// tworzy tabele jezeli nie ma

    bool zapiszStanGry(Game &g);
    bool wczytajStanGry(Game &g);

    bool dodajDoRankingu(const std::string &nick, int sekundy);
    std::vector<WpisRankingu> pobierzRanking(int limit);

private:
    std::string sciezkaPliku;
    void *db;//sqlite3* handle - void* zeby nie wciagac sqlite3.h tu
};

#endif