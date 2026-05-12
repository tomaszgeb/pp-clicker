# PP Clicker - Droga do Inzyniera

Projekt na zajecia Programowanie Strukturalne i Obiektowe (PSiO).

Politechnika Poznanska, AiR, semestr 2.

## Cel gry

Zdobyc 210 punktow ECTS klikajac w logo PP. Mozna kupowac ulepszenia za zarobione punkty.

## Sklad zespolu

| Osoba         | Co robi                                              |
|---------------|------------------------------------------------------|
| Tomasz Gebka  | silnik gry, klikanie, zdarzenia losowe i kary        |
| Jan Faferek   | SQLite (zapisy, ranking), timer dochodu pasywnego    |
| Jakub Glinka  | GUI (SFML), pop-upy, system sklepu, walidacja punktow|

## Stack

- C++17
- SFML 2.5+ (GUI)
- SQLite3 (zapisy, leaderboard)
- CMake (build)

## Jak zbudowac

```
mkdir build && cd build
cmake ..
make
./pp-clicker
```

## Termin oddania

12 czerwca 2026
