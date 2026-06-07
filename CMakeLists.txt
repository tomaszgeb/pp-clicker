cmake_minimum_required(VERSION 3.10)
project(pp-clicker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# na razie tylko pliki Tomka - Janek i Kuba dorzuca swoje
# jak juz beda commitowac swoje pliki
add_executable(pp-clicker
    src/main.cpp
    src/Game.cpp
    src/RandomEvent.cpp
)

target_include_directories(pp-clicker PRIVATE src)

# TODO: dorzucic SFML i sqlite3 jak Kuba i Janek skoncza
# find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
# target_link_libraries(pp-clicker sfml-graphics sfml-window sfml-system sqlite3)
