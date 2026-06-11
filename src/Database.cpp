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

    // tabela stanu sklepu (ile kazdego itemu kupiles)
    const char *sql3 =
        "CREATE TABLE IF NOT EXISTS stan_sklepu ("
        "idx INTEGER PRIMARY KEY,"
        "ile_posiadanych INTEGER"
        ");";
    sqlite3_exec(handle, sql3, 0, 0, &err);
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

// pomocnicza struktura do przekazania wyniku z callbacka
struct DaneStanu {
    int punkty;
    int ects;
    int mocKliku;
    int dochodPasywny;
    bool znaleziono;
};

// callback wywolywany przez sqlite3_exec dla kazdego wiersza
static int callbackStan(void *data, int kolumn, char **wartosci, char **nazwy) {
    (void)nazwy;//nieuzywane ale wymagane przez signature sqlite3
    DaneStanu *d = (DaneStanu*)data;
    if(kolumn >= 4) {
        d->punkty = wartosci[0] ? atoi(wartosci[0]) : 0;
        d->ects = wartosci[1] ? atoi(wartosci[1]) : 0;
        d->mocKliku = wartosci[2] ? atoi(wartosci[2]) : 1;
        d->dochodPasywny = wartosci[3] ? atoi(wartosci[3]) : 0;
        d->znaleziono = true;
    }
    return 0;
}

bool Database::wczytajStanGry(Game &g) {
    sqlite3 *handle = (sqlite3*)db;
    DaneStanu d;
    d.znaleziono = false;
    d.punkty = 0; d.ects = 0; d.mocKliku = 1; d.dochodPasywny = 0;

    sqlite3_exec(handle,
        "SELECT punkty, ects, moc_kliku, dochod_pasywny FROM stan_gry WHERE id=1;",
        callbackStan, &d, 0);

    if(!d.znaleziono) return false;

    // ustawiamy w Game caly stan naraz
    g.ustawStan(d.punkty, d.ects, d.mocKliku, d.dochodPasywny);
    return true;
}

// zapis stanu sklepu, iterujemy po wszystkich itemach i wpisujemy ile_posiadanych
bool Database::zapiszStanSklepu(Shop &s) {
    sqlite3 *handle = (sqlite3*)db;
    // czyscimy stara zawartosc
    sqlite3_exec(handle, "DELETE FROM stan_sklepu;", 0, 0, 0);

    for(int i = 0; i < s.liczbaItemow(); i++) {
        ItemSklepu it = s.getItem(i);
        char sql[256];
        snprintf(sql, sizeof(sql),
            "INSERT INTO stan_sklepu (idx, ile_posiadanych) VALUES (%d, %d);",
            i, it.ilePosiadanych);
        char *err = 0;
        sqlite3_exec(handle, sql, 0, 0, &err);
        if(err) { sqlite3_free(err); return false; }
    }
    return true;
}

// pomocnicza struktura na wynik wczytywania sklepu
struct DaneSklepu {
    Shop *sklep;
};

static int callbackSklep(void *data, int kolumn, char **wartosci, char **nazwy) {
    (void)nazwy;//nieuzywane ale wymagane przez signature sqlite3
    DaneSklepu *d = (DaneSklepu*)data;
    if(kolumn >= 2 && wartosci[0] && wartosci[1]) {
        int idx = atoi(wartosci[0]);
        int ile = atoi(wartosci[1]);
        d->sklep->ustawIloscPosiadanych(idx, ile);
    }
    return 0;
}

bool Database::wczytajStanSklepu(Shop &s) {
    sqlite3 *handle = (sqlite3*)db;
    DaneSklepu d;
    d.sklep = &s;
    sqlite3_exec(handle,
        "SELECT idx, ile_posiadanych FROM stan_sklepu;",
        callbackSklep, &d, 0);
    return true;
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

// callback wywolywany przez sqlite3_exec dla kazdego wiersza z rankingiem
static int callbackRanking(void *data, int kolumn, char **wartosci, char **nazwy) {
    (void)nazwy;//nieuzywane ale wymagane przez signature sqlite3
    std::vector<WpisRankingu> *v = (std::vector<WpisRankingu>*)data;
    if(kolumn >= 2) {
        WpisRankingu w;
        w.nick = wartosci[0] ? wartosci[0] : "anon";
        w.sekundy = wartosci[1] ? atoi(wartosci[1]) : 0;
        v->push_back(w);
    }
    return 0;
}

std::vector<WpisRankingu> Database::pobierzRanking(int limit) {
    std::vector<WpisRankingu> wynik;
    sqlite3 *handle = (sqlite3*)db;
    char sql[256];
    // sortujemy rosnaco po sekundach (najszybsi na gorze)
    snprintf(sql, sizeof(sql),
        "SELECT nick, sekundy FROM ranking ORDER BY sekundy ASC LIMIT %d;", limit);
    sqlite3_exec(handle, sql, callbackRanking, &wynik, 0);
    return wynik;
}