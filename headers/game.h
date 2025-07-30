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
    SDL_Window* window{};   // ������ �� ����
    SDL_Renderer* renderer{}; // ������ �� ��������
    SDL_Event event{};     // ������� ������� ������
    float timer{}, delay{};
    bool gameLoop{};
    int dir{}, num{}, maxNum = 4;
};
