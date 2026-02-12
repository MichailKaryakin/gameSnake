#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "input.h"
#include "sprite.h"

class Game {
public:
    Game();

    ~Game();

private:
    void create();

    void play();

    void update();

    void render();

    void InitSDL();

    static void callMenu(SDL_Renderer* renderer);

    static void callFinalScreen(SDL_Renderer* renderer, int num);

    Texture texture;
    Input input;
    Sprite item, snake, background;
    SDL_Rect snakeBody[100]{};
    SDL_Rect fruit{};
    SDL_Window* window{};   // ссылка на окно
    SDL_Renderer* renderer{}; // ссылка на рендерер
    SDL_Event event{};     // события нажатия клавиш
    float timer{}, delay{};
    bool gameLoop{};
    int dir{}, num{}, maxNum = 4;
};
