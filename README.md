# PP Clicker. Droga do Inzyniera

Projekt na zajecia Programowanie Strukturalne i Obiektowe (PSiO).

Politechnika Poznanska, AiR, semestr 2.

## O co chodzi w grze

Klikasz w logo Politechniki i dostajesz punkty. Za punkty kupujesz ECTS,
gdy uzbierasz 210 ECTS to wygrywasz (zostajesz inzynierem).

Mozesz tez kupowac ulepszenia (Kawa, Baza Kolosow, Kolega, Gemini Pro)
ktore zwiekszaja moc klikania albo daja punkty co sekunde.

Co jakis czas wyskakuja zdarzenia losowe z karami (lore z prezentacji).
Trzeba kliknac OK zeby kontynuowac.

## Kto co robil

| Osoba         | Co robil                                                |
|---------------|---------------------------------------------------------|
| Tomasz Gebka  | silnik gry, mechanika klikania, zdarzenia losowe i kary |
| Jan Faferek   | SQLite (zapisy stanu, ranking), timer dochodu pasywnego |
| Jakub Glinka  | GUI w SFML, pop upy, sklep z 4 itemami                  |

## Czego potrzeba zeby zbudowac

Wystarczy:
- kompilator C++17 (g++ albo clang albo MSVC)
- CMake 3.14 albo nowszy
- polaczenie z internetem (tylko za pierwszym razem, do pobrania SFML)

SFML pobiera sie automatycznie przez CMake FetchContent jak nie masz go
zainstalowanego. SQLite mamy w repo (amalgamation, jeden plik C),
nie trzeba nic instalowac.

## Jak zbudowac na macOS

```
git clone https://github.com/tomaszgeb/pp-clicker.git
cd pp-clicker
mkdir build
cd build
cmake ..
cmake --build .
cd ..
./build/pp-clicker
```

Jak masz brew to mozesz dograc SFML wczesniej, wtedy CMake nic nie pobiera:

```
brew install sfml@2
```

## Jak zbudowac na Linuxie (Ubuntu, Debian)

```
sudo apt install g++ cmake git

git clone https://github.com/tomaszgeb/pp-clicker.git
cd pp-clicker
mkdir build
cd build
cmake ..
cmake --build .
cd ..
./build/pp-clicker
```

Mozesz tez dograc SFML wczesniej zeby CMake go nie pobieral:

```
sudo apt install libsfml-dev
```

## Jak zbudowac na Windowsie (Qt Creator albo Visual Studio)

### Sposob 1, Qt Creator z MinGW

1. Pobierz Qt Creator z https://www.qt.io/download (wersja Community)
   przy instalacji zaznacz MinGW kompilator

2. Pobierz nasze repo, najlatwiej jako ZIP:
   wejdz na https://github.com/tomaszgeb/pp-clicker
   klik zielony Code, potem Download ZIP, rozpakuj

3. W Qt Creator klik File, Open File or Project, wybierz CMakeLists.txt
   z folderu pp-clicker

4. Configure Project, zaznacz Kit z MinGW, klik Configure Project

5. CMake pobierze SFML automatycznie (pierwszym razem trwa 5 do 10 minut,
   pozniej juz nie). Jak skonczy, klik Build (Ctrl+B), potem Run (Ctrl+R).

### Sposob 2, Visual Studio

1. Pobierz Visual Studio Community z https://visualstudio.microsoft.com
   przy instalacji zaznacz "Desktop development with C++"

2. Pobierz repo (ZIP jak wyzej albo git clone)

3. W Visual Studio klik File, Open, CMake, wybierz CMakeLists.txt

4. Visual Studio sam wszystko skonfiguruje, klik Build, Build All

### Sposob 3, MSYS2 z konsoli (dla wytrwalych)

```
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-make git

git clone https://github.com/tomaszgeb/pp-clicker.git
cd pp-clicker
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
./pp-clicker.exe
```

## Jak uruchomic

Z folderu projektu (zeby zaladowaly sie obrazki z assets):

```
./build/pp-clicker
```

Na Windowsie .exe jest w folderze build, jak uruchamiasz przez Qt Creator
to dziala automatycznie.

## Sterowanie

- LPM w logo PP. dodaje punkty (animacja "+N" leci do gory)
- LPM w item w sklepie z prawej. kupuje (jak masz punkty)
- LPM w zielony przycisk "Kup ECTS" na dole. zamienia 1000 pkt na 1 ECTS
- Cel: 210 ECTS

Po wystąpieniu zdarzenia losowego (Afera Budzikowa, Zenon, Przewod, Klatwa,
Lawka troski) wyskakuje popup, klikasz OK zeby kontynuowac.

## Struktura projektu

```
pp-clicker/
  CMakeLists.txt
  README.md
  assets/
    arial.ttf          (czcionka do tekstu w SFML)
    logo_pp.png        (logo Politechniki ze slajdu prezentacji)
    kawa.png           (ikonki itemow ze sklepu, tez ze slajdu)
    baza.png
    kolega.png
    gemini.png
  src/
    main.cpp           (entry point, podlacza wszystkie klasy)
    Game.h, Game.cpp           (silnik gry Tomka)
    RandomEvent.h, RandomEvent.cpp  (zdarzenia losowe Tomka)
    Database.h, Database.cpp        (SQL save/load Janka)
    Timer.h, Timer.cpp              (watek dochodu pasywnego Janka)
    Shop.h, Shop.cpp                (sklep Kuby)
    GUI.h, GUI.cpp                  (okno SFML Kuby)
    sqlite3.c, sqlite3.h            (amalgamation SQLite, pobrane z sqlite.org)
```

## Biblioteki

- SFML 2.6 (graphics, window, system). Pobierana automatycznie przez CMake
  FetchContent jak nie masz lokalnie
- SQLite3 (amalgamation, kompilowany razem z naszym kodem)
- Standard C++ (string, vector, thread, chrono, atomic gdzie potrzeba)

## Termin oddania

13 czerwca 2026 (sobota), 12:00.
