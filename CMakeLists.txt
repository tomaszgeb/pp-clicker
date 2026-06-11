cmake_minimum_required(VERSION 3.14)
project(pp-clicker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# probujemy znalezc SFML zainstalowany lokalnie
# jak nie ma to CMake sciagnie go z GitHuba i sam skompiluje
# zeby kazdy mial taka sama wersje 2.6.x
find_package(SFML 2.6 COMPONENTS graphics window system QUIET)
if(NOT SFML_FOUND)
    message(STATUS "SFML nie znaleziony, pobieram z GitHuba (chwile to potrwa)")
    include(FetchContent)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
    )
    # wylaczamy modulki ktorych nie uzywamy zeby sie szybciej kompilowalo
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SFML)
endif()

# wszystkie nasze pliki + sqlite3 jako amalgamation (kompiluje sie razem)
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
