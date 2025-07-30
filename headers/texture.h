#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <map>

class Texture {
public:
    void setRender(SDL_Renderer* renderer);

    Texture();

    ~Texture();

    void Dispose();

    SDL_Texture* getTexture(const std::string& name);

private:
    SDL_Texture* loadTexture(const std::string& name);

    SDL_Renderer* _renderer{};

    std::map<std::string, SDL_Texture*> _textureMap;
};
