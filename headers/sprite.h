#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Sprite {
public:
    Sprite();

    ~Sprite();

    void draw(SDL_Renderer* renderer);  // выводим спрайт

    void setPosition(const float& x, const float& y);

    void setScale(const float& x, const float& y);

    void setTexture(SDL_Texture* texture);  // устанавливаем текстуру
private:
    void init();

    float _angle{};
    SDL_FPoint _position{};
    SDL_FPoint _scale{};
    SDL_Texture* _texture{};
    SDL_Rect _sourceRect{};
    SDL_Color _color{};
};
