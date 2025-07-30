#include "game.h"
#include "globals.h"
#include "menu.h"
#include "finscr.h"

Game::Game() {
    create();
    callMenu(this->renderer);
    play();
    callFinalScreen(this->renderer, this->maxNum);
}

Game::~Game() {
    this->texture.Dispose();
    this->input.Dispose();
    if (this->renderer) SDL_DestroyRenderer(this->renderer);  // удал€ем renderer
    this->renderer = nullptr;
    if (this->window) SDL_DestroyWindow(this->window); // удалаем window
    this->window = nullptr;
    SDL_Quit();
}

void Game::create() {
    this->gameLoop = true;
    InitSDL();

    this->texture.setRender(this->renderer);

    this->num = 4;        // длина нашей змейки
    this->timer = 0;        // таймер дл€ шага
    this->dir = 0;        // направление змейки
    this->delay = 0.1;    // скорость звижени€ змейки

    // назначаем текстуры в спрайт
    this->item.setTexture(this->texture.getTexture(
            R"(C:\Users\micha\Documents\programming\code\cpp\labs\game_snake\content\sprites\green.png)"));
    this->snake.setTexture(this->texture.getTexture(
            R"(C:\Users\micha\Documents\programming\code\cpp\labs\game_snake\content\sprites\red.png)"));
    this->background.setTexture(this->texture.getTexture(
            R"(C:\Users\micha\Documents\programming\code\cpp\labs\game_snake\content\sprites\white.png)"));

    // масштабируем спрайты под размер пол€
    this->item.setScale(::scale_W, ::scale_H);
    this->snake.setScale(::scale_W, ::scale_H);
    this->background.setScale(::scale_W, ::scale_H);

    this->fruit.x = this->fruit.y = 10;
    this->snakeBody[0].x = 0;
    this->snakeBody[0].y = 0;
}

void Game::InitSDL() {
    Uint32 flagsW = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    this->window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ::width_pixel, ::height_pixel, flagsW);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void Game::play() {
    while (this->gameLoop) {
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0); // цвет обнулени€ экрана черный
        SDL_RenderClear(this->renderer);

        update();
        render();
    }
}

void Game::update() {
    this->input.update(this->event);

    if (this->input.exit) this->gameLoop = false;

    this->timer += 0.01;

    if (this->input.isKeyDown(SDLK_LEFT) && this->dir != 2) this->dir = 1;
    if (this->input.isKeyDown(SDLK_RIGHT) && this->dir != 1) this->dir = 2;
    if (this->input.isKeyDown(SDLK_UP) && this->dir != 0) this->dir = 3;
    if (this->input.isKeyDown(SDLK_DOWN) && this->dir != 3) this->dir = 0;

    if (this->timer > this->delay) {
        this->timer = 0;

        // движени€ змейки добиваемс€ путем копировани€ €чеек
        for (int i = this->num; i > 0; --i) {
            this->snakeBody[i].x = this->snakeBody[i - 1].x;
            this->snakeBody[i].y = this->snakeBody[i - 1].y;
        }

        // двигаем змейку
        if (this->dir == 0) this->snakeBody[0].y += 1;
        if (this->dir == 1) this->snakeBody[0].x -= 1;
        if (this->dir == 2) this->snakeBody[0].x += 1;
        if (this->dir == 3) this->snakeBody[0].y -= 1;

        // попалось €блоко съели
        if ((this->snakeBody[0].x == this->fruit.x) && (this->snakeBody[0].y == this->fruit.y)) {
            bool done;
            do
            {
                this->fruit.x = rand() % ::width_cell;
                this->fruit.y = rand() % ::height_cell;
                done = true;
                for (int i = num; i >= 0; --i) {
                    if (this->snakeBody[i].x == this->fruit.x && this->snakeBody[i].y == this->fruit.y) {
                        done = false;
                    }
                }
            } while (!done);
            ++this->num;
            if (this->num > this->maxNum) {
                this->maxNum = this->num;
            }
        }

        if (this->snakeBody[0].x >= ::width_cell) {
            this->gameLoop = false;
        }
        if (this->snakeBody[0].y >= ::height_cell) {
            this->gameLoop = false;
        }
        if (this->snakeBody[0].x < 0) {
            this->gameLoop = false;
        }
        if (this->snakeBody[0].y < 0) {
            this->gameLoop = false;
        }

        // откусываем хвост, если врезались в себ€
        for (int i = 1; i < this->num; i++) {
            if (this->snakeBody[0].x == this->snakeBody[i].x && this->snakeBody[0].y == this->snakeBody[i].y) {
                this->num = i;
            }
        }
    }
}

void Game::render() {
    // выводим поле
    for (int x = 0; x < ::width_cell; x++)
        for (int y = 0; y < ::height_cell; y++) {
            this->background.setPosition(x * ::sizeCell, y * ::sizeCell);
            this->background.draw(this->renderer);
        }

    // выводим змейку
    for (int i = 0; i < num; i++) {
        this->snake.setPosition(this->snakeBody[i].x * ::sizeCell, this->snakeBody[i].y * ::sizeCell);
        this->snake.draw(this->renderer);
    }

    // назначем позицию и выводим €блоко
    this->item.setPosition(this->fruit.x * ::sizeCell, this->fruit.y * ::sizeCell);
    this->item.draw(this->renderer);

    SDL_RenderPresent(this->renderer);
}

void Game::callMenu(SDL_Renderer* renderer) {
    (Menu(renderer));
}

void Game::callFinalScreen(SDL_Renderer* renderer, int num) {
    (FinalScreen(renderer, num));
}
