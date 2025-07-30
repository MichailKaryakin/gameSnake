#pragma once

#include <string>
#include <map>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include "input.h"
#include "cstdio"

class FinalScreen {
private:
    static void get_text_and_rect(SDL_Renderer* renderer, int x, int y, const std::string& text, TTF_Font* font,
                                  SDL_Texture** texture, SDL_Rect* rect);

    static void addScore(int score);

    static void showFinalScreen(SDL_Renderer* renderer);

    static void vectorSort(std::vector<std::string>& nicknames, std::vector<std::string>& scores);

    static void vectorRead(std::vector<std::string>& nicknames, std::vector<std::string>& scores);

    static void prepareText(SDL_Renderer* renderer, std::vector<SDL_Rect>& rects_1, std::vector<SDL_Rect>& rects_2,
                            std::vector<SDL_Texture*>& textures_1, std::vector<SDL_Texture*>& textures_2,
                            std::vector<std::string>& nicknames, std::vector<std::string>& scores, TTF_Font* font1);

    static bool sortByVal(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b);

public:
    explicit FinalScreen(SDL_Renderer* renderer, int score);
};
