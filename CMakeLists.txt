cmake_minimum_required(VERSION 3.10)
project(pp-clicker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# wszystkie nasze pliki + sqlite3 amalgamation
# (dorzucilismy sqlite3.c do repo zeby nie trzeba bylo instalowac
#  sqlita osobno - kompiluje sie razem z reszta)
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

# SFML - jedyna zewnetrzna biblioteka jaka trzeba zainstalowac
# Mac: brew install sfml@2
# Linux: sudo apt install libsfml-dev
# Windows: pobierz SFML 2.6.x z sfml-dev.org i rozpakuj do C:/SFML
if(APPLE)
    # macOS Apple Silicon - brew keg-only
    set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml@2" ${CMAKE_PREFIX_PATH})
endif()

if(WIN32)
    # Windows - SFML rozpakowane w C:/SFML
    set(SFML_DIR "C:/SFML/lib/cmake/SFML")
endif()

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
target_link_libraries(pp-clicker sfml-graphics sfml-window sfml-system)

# pthread - na Linux/Mac, na Windowsie MinGW tez to ma
if(NOT WIN32)
    target_link_libraries(pp-clicker pthread)
endif()
