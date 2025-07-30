cmake_minimum_required(VERSION 3.20)
project(game_snake)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_IMAGE REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

find_package(SDL2_TTF REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

include_directories(headers)

add_executable(game_snake
        headers/game.h
        headers/input.h
        headers/texture.h
        headers/sprite.h
        src/game.cpp
        src/main.cpp
        src/input.cpp
        src/texture.cpp
        src/sprite.cpp headers/globals.h headers/menu.h src/menu.cpp headers/finscr.h src/finscr.cpp)

target_link_libraries(game_snake ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -mwindows)
