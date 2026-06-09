# PP Clicker - Droga do Inzyniera

Projekt na zajecia Programowanie Strukturalne i Obiektowe (PSiO).

Politechnika Poznanska, AiR, semestr 2.

## Cel gry

Zdobyc 210 punktow ECTS klikajac w logo PP. Mozna kupowac ulepszenia za zarobione punkty.
Co jakis czas wyskakuja zdarzenia losowe z karami z lore PP (Adam D., Zenon Z. itp).

## Sklad zespolu

| Osoba         | Co robi                                              |
|---------------|------------------------------------------------------|
| Tomasz Gebka  | silnik gry, klikanie, zdarzenia losowe i kary        |
| Jan Faferek   | SQLite (zapisy, ranking), timer dochodu pasywnego    |
| Jakub Glinka  | GUI (SFML), pop-upy, system sklepu, walidacja punktow|

## Wymagania

- C++17 (g++ / clang++ / MSVC)
- CMake 3.10+
- SFML 2.6 (jedyna zewnetrzna biblioteka)
- SQLite3 NIE TRZEBA instalowac - mamy amalgamation w repo (src/sqlite3.c)

## Instalacja SFML

### macOS
```
brew install sfml@2
```

### Linux (Ubuntu/Debian)
```
sudo apt install libsfml-dev cmake g++
```

### Windows
1. Pobierz SFML 2.6.x dla MinGW: https://www.sfml-dev.org/download/sfml/2.6.2/
2. Rozpakuj do `C:\SFML`
3. Po zbudowaniu skopiuj `C:\SFML\bin\sfml-graphics-2.dll`, `sfml-window-2.dll`, `sfml-system-2.dll` do folderu z .exe

## Build

### Przez CMake (zalecane - Qt Creator / Visual Studio / wiersz polecen)

```
git clone https://github.com/tomaszgeb/pp-clicker.git
cd pp-clicker
mkdir build
cd build
cmake ..
cmake --build .
```

Po zbudowaniu uruchom z folderu projektu (zeby assets/ byly w pwd):
```
cd ..
./build/pp-clicker
```

### Przez Qt Creator
1. File -> Open File or Project -> wybierz `CMakeLists.txt`
2. Configure Project (wybierz Kit z MinGW lub innym)
3. Ctrl+B (build), Ctrl+R (run)

### Recznie przez g++ (bez CMake)
```
# macOS Apple Silicon
g++ -std=c++17 -I src -I /opt/homebrew/opt/sfml@2/include src/*.cpp src/sqlite3.c -L /opt/homebrew/opt/sfml@2/lib -lsfml-graphics -lsfml-window -lsfml-system -pthread -o pp-clicker

# Linux
g++ -std=c++17 -I src src/*.cpp src/sqlite3.c -lsfml-graphics -lsfml-window -lsfml-system -pthread -o pp-clicker
```

## Uruchomienie

```
./pp-clicker
```

Otworzy sie okno SFML 900x700 z gra. Asetty (logo PP, ikonki, czcionka) sa w folderze `assets/` - musza byc relatywnie wzgledem PWD.

## Sterowanie

- LPM na logo PP - klik (dodaje punkty)
- LPM na item w sklepie z prawej - kupno (jezeli stac)
- LPM na "Kup ECTS" w lewym dolnym rogu - zamiana 1000 pkt na 1 ECTS
- Cel: 210 ECTS = wygrana

## Struktura projektu

```
pp-clicker/
├── CMakeLists.txt
├── README.md
├── assets/         # obrazki z prezentacji + czcionka
└── src/
    ├── main.cpp        # entry point + integracja
    ├── Game.h/cpp      # silnik gry (Tomek)
    ├── RandomEvent.h/cpp  # zdarzenia losowe i kary (Tomek)
    ├── Database.h/cpp  # SQLite save/load + ranking (Janek)
    ├── Timer.h/cpp     # watek dochodu pasywnego (Janek)
    ├── Shop.h/cpp      # sklep z 4 itemami (Kuba)
    ├── GUI.h/cpp       # okno SFML, popupy, sklep (Kuba)
    ├── sqlite3.c       # SQLite amalgamation (zewnetrzny, w repo)
    └── sqlite3.h
```

## Termin oddania

13 czerwca 2026 (sobota), 12:00.
