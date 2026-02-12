#include "texture.h"

Texture::Texture() = default;

void Texture::setRender(SDL_Renderer* renderer) {
    this->_renderer = renderer;
}

void Texture::Dispose() {
    for (auto & i : this->_textureMap) {
        SDL_DestroyTexture(i.second);
    }

    this->_textureMap.clear();
}

Texture::~Texture() {
    Dispose();
}

SDL_Texture* Texture::getTexture(const std::string& name) {
    auto mit = this->_textureMap.find(name);

    if (mit == this->_textureMap.end()) {
        SDL_Texture* newTexture = loadTexture(name);

        this->_textureMap.insert(make_pair(name, newTexture));

        return newTexture;
    }

    return mit->second;
}

SDL_Texture* Texture::loadTexture(const std::string& name) {
    SDL_Surface* loadedImage = IMG_Load(name.c_str());

    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(this->_renderer, loadedImage);

    SDL_FreeSurface(loadedImage);

    return newTexture;
}
	