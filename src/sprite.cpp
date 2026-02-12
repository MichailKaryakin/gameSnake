#include "sprite.h"

Sprite::Sprite() = default;

void Sprite::init() {
    this->_scale = {1.0, 1.0};
    this->_position = {0, 0};
    this->_color = {255, 255, 255, 255};
    this->_sourceRect.x = this->_sourceRect.y = 0;
    this->_angle = 0;
}

Sprite::~Sprite() = default;

void Sprite::setPosition(const float& x, const float& y) {
    this->_position = {x, y};
}

void Sprite::setScale(const float& x, const float& y) {
    this->_scale = {x, y};
}

void Sprite::setTexture(SDL_Texture* texture)  // устанавливаем текстуру
{
    this->_texture = texture;

    SDL_QueryTexture(this->_texture, nullptr, nullptr, &this->_sourceRect.w, &this->_sourceRect.h);

    init();
}

void Sprite::draw(SDL_Renderer* renderer) {
    SDL_FPoint Centre = {0.0, 0.0};
    Centre.x *= this->_scale.x;
    Centre.y *= this->_scale.y;

    SDL_FRect rectWin{
            this->_position.x - Centre.x,
            this->_position.y - Centre.y,
            this->_sourceRect.w * this->_scale.x,
            this->_sourceRect.h * this->_scale.y
    };

    SDL_SetTextureColorMod(this->_texture, this->_color.r, this->_color.g, this->_color.b);
    SDL_SetTextureAlphaMod(this->_texture, this->_color.a);
    SDL_RenderCopyExF(renderer, this->_texture, &_sourceRect, &rectWin, this->_angle, &Centre, SDL_FLIP_NONE);
}
