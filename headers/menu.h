#pragma once

#include <string>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include "input.h"

class Menu {
private:
    static void get_text_and_rect(SDL_Renderer* renderer, int x, int y, const std::string& text,
                                  TTF_Font* font, SDL_Texture** texture, SDL_Rect* rect);

    static void addRecord(std::string& nickname);

    static void showTitleScreen(SDL_Renderer* renderer);

    static void setNickname(SDL_Renderer* renderer);

    static bool symbolCondition(Input& input);

public:
    explicit Menu(SDL_Renderer* renderer);
};
