cmake_minimum_required(VERSION 3.10)
project(pp-clicker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML - jedyna zewnetrzna zaleznosc
# jak nie znajdzie - ustaw SFML_DIR np. -DSFML_DIR=C:/SFML/lib/cmake/SFML
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# wszystkie nasze pliki + sqlite3 (amalgamation, dorzucone do repo)
add_executable(pp-clicker
    src/main.cpp
    src/Game.cpp
    src/RandomEvent.cpp
    src/Database.cpp
    src/Timer.cpp
    src/Shop.cpp
    src/GUI.cpp
    src/sqlite3.c
)

target_include_directories(pp-clicker PRIVATE src)
target_link_libraries(pp-clicker sfml-graphics sfml-window sfml-system)
