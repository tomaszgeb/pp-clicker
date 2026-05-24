#include "Database.h"
#include <sqlite3.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>

Database::Database(const std::string &plik) {
    sciezkaPliku = plik;
    db = 0;
}

Database::~Database() {
    if(db) sqlite3_close((sqlite3*)db);
}

// na razie tylko otwarcie pliku bazy
bool Database::init() {
    sqlite3 *handle;
    int r = sqlite3_open(sciezkaPliku.c_str(), &handle);
    if(r != SQLITE_OK) {
        std::cerr << "blad otwarcia bazy: " << sqlite3_errmsg(handle) << std::endl;
        return false;
    }
    db = handle;

    // tabela stanu gry - jeden wpis
    const char *sql1 =
        "CREATE TABLE IF NOT EXISTS stan_gry ("
        "id INTEGER PRIMARY KEY,"
        "punkty INTEGER,"
        "ects INTEGER,"
        "moc_kliku INTEGER,"
        "dochod_pasywny INTEGER"
        ");";
    char *err = 0;
    sqlite3_exec(handle, sql1, 0, 0, &err);
    if(err) {
        std::cerr << err << std::endl;
        sqlite3_free(err);
        return false;
    }

    // tabela rankingu
    const char *sql2 =
        "CREATE TABLE IF NOT EXISTS ranking ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nick TEXT,"
        "sekundy INTEGER"
        ");";
    sqlite3_exec(handle, sql2, 0, 0, &err);
    if(err) {
        std::cerr << err << std::endl;
        sqlite3_free(err);
        return false;
    }

    return true;
}

bool Database::zapiszStanGry(Game &g) {
    sqlite3 *handle = (sqlite3*)db;
    // kasujemy stary wpis i wpisujemy nowy
    sqlite3_exec(handle, "DELETE FROM stan_gry;", 0, 0, 0);

    char sql[512];
    snprintf(sql, sizeof(sql),
        "INSERT INTO stan_gry (id, punkty, ects, moc_kliku, dochod_pasywny) "
        "VALUES (1, %d, %d, %d, %d);",
        g.getPunkty(), g.getEcts(), g.getMocKliku(), g.getDochodPasywny());

    char *err = 0;
    sqlite3_exec(handle, sql, 0, 0, &err);
    if(err) {
        sqlite3_free(err);
        return false;
    }
    return true;
}

bool Database::wczytajStanGry(Game &g) {
    //TODO
    return false;
}

bool Database::dodajDoRankingu(const std::string &nick, int sekundy) {
    sqlite3 *handle = (sqlite3*)db;
    char sql[512];
    snprintf(sql, sizeof(sql),
        "INSERT INTO ranking (nick, sekundy) VALUES ('%s', %d);",
        nick.c_str(), sekundy);
    char *err = 0;
    sqlite3_exec(handle, sql, 0, 0, &err);
    if(err) {
        sqlite3_free(err);
        return false;
    }
    return true;
}

std::vector<WpisRankingu> Database::pobierzRanking(int limit) {
    std::vector<WpisRankingu> wynik;
    //TODO
    return wynik;
}