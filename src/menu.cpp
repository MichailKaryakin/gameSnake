#include "menu.h"

void Menu::get_text_and_rect(SDL_Renderer* renderer, int x, int y, const std::string& text, TTF_Font* font,
                             SDL_Texture** texture,
                             SDL_Rect* rect) {
    int text_width;
    int text_height;
    SDL_Surface* surface;
    SDL_Color textColor = {255, 255, 255, 0};

    const char* Text = text.c_str();
    surface = TTF_RenderText_Solid(font, Text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}

Menu::Menu(SDL_Renderer* renderer) {
    showTitleScreen(renderer);
    setNickname(renderer);
}

void Menu::showTitleScreen(SDL_Renderer* renderer) {
    TTF_Init();
    TTF_Font* font1 = TTF_OpenFont(
            R"(C:\Users\micha\Documents\programming\code\cpp\labs\game_snake\content\fonts\font2.ttf)",
            90);
    TTF_Font* font2 = TTF_OpenFont(
            R"(C:\Users\micha\Documents\programming\code\cpp\labs\game_snake\content\fonts\font2.ttf)",
            40);

    SDL_Event event;
    SDL_Rect rect1, rect2, rect3;
    SDL_Texture* texture1, * texture2, * texture3;
    bool proceed = false;

    get_text_and_rect(renderer, 395, 260, "Snake", font1, &texture1, &rect1);
    get_text_and_rect(renderer, 395, 340, "Game", font1, &texture2, &rect2);
    get_text_and_rect(renderer, 345, 500, "press space button", font2, &texture3, &rect3);

    Input input;
    while (!proceed) {
        input.update(event);

        if (input.isKeyDown(SDLK_SPACE)) proceed = true;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture1, nullptr, &rect1);
        SDL_RenderCopy(renderer, texture2, nullptr, &rect2);
        SDL_RenderCopy(renderer, texture3, nullptr, &rect3);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture3);
    TTF_Quit();
}

void Menu::setNickname(SDL_Renderer* renderer) {
    TTF_Init();
    TTF_Font* font1 = TTF_OpenFont(
            R"(C:\Users\micha\Documents\programming\code\cpp\labs\game_snake\content\fonts\font1.ttf)",
            70);
    TTF_Font* font2 = TTF_OpenFont(
            R"(C:\Users\micha\Documents\programming\code\cpp\labs\game_snake\content\fonts\font1.ttf)",
            40);

    SDL_Event event;
    SDL_Rect rect1, rect2;
    SDL_Texture* texture1, * texture2;
    bool proceed = false;

    std::string nickname = " ";
    get_text_and_rect(renderer, 185, 200, "Enter the nickname:", font1, &texture1, &rect1);

    Input input;
    while (!proceed) {
        input.update(event);
        char lastKey = input.getLastKey();
        char preLastKey = input.getPreLastKey();

        if (input.isKeyDown(SDLK_SPACE) && nickname.front() != ' ') {
            proceed = true;
        } else if (nickname.size() < 14 && symbolCondition(input)) {
            if (lastKey != ' ' && lastKey != nickname.back()) {
                if (nickname[0] == ' ') {
                    nickname[0] = lastKey;
                } else {
                    nickname.push_back(lastKey);
                }
            }
            if (lastKey != ' ' && preLastKey == lastKey) {
                nickname.push_back(lastKey);
                input.setPreLastKeyToInit();
            }
        }

        get_text_and_rect(renderer, 350, 300, nickname, font2, &texture2, &rect2);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture1, nullptr, &rect1);
        SDL_RenderCopy(renderer, texture2, nullptr, &rect2);

        SDL_RenderPresent(renderer);
    }

    addRecord(nickname);

    TTF_Quit();
}

void Menu::addRecord(std::string& nickname) {
    std::string filePath = R"(C:\Users\micha\Documents\programming\code\cpp\labs\game_snake\content\data\nicknames.txt)";
    FILE* file = fopen(filePath.c_str(), "a");
    nickname.push_back(' ');
    fputs(nickname.c_str(), file);
    fclose(file);
}

bool Menu::symbolCondition(Input& input) {
    if (input.isKeyDown(SDLK_q) || input.isKeyDown(SDLK_w) || input.isKeyDown(SDLK_e) || input.isKeyDown(SDLK_r) ||
        input.isKeyDown(SDLK_t) || input.isKeyDown(SDLK_y) || input.isKeyDown(SDLK_u) || input.isKeyDown(SDLK_i) ||
        input.isKeyDown(SDLK_o) || input.isKeyDown(SDLK_p) || input.isKeyDown(SDLK_a) || input.isKeyDown(SDLK_s) ||
        input.isKeyDown(SDLK_d) || input.isKeyDown(SDLK_f) || input.isKeyDown(SDLK_g) || input.isKeyDown(SDLK_h) ||
        input.isKeyDown(SDLK_j) || input.isKeyDown(SDLK_k) || input.isKeyDown(SDLK_l) || input.isKeyDown(SDLK_z) ||
        input.isKeyDown(SDLK_x) || input.isKeyDown(SDLK_c) || input.isKeyDown(SDLK_v) || input.isKeyDown(SDLK_b) ||
        input.isKeyDown(SDLK_n) || input.isKeyDown(SDLK_m)) {
        return true;
    } else {
        return false;
    }
}
