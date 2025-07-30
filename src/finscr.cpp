#include <algorithm>
#include "finscr.h"

void FinalScreen::get_text_and_rect(SDL_Renderer* renderer, int x, int y, const std::string& text, TTF_Font* font,
                                    SDL_Texture** texture, SDL_Rect* rect) {
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

void FinalScreen::addScore(int score) {
    std::string filePath = R"(C:\Users\micha\Documents\programming\code\cpp\labs\game_snake\content\data\scores.txt)";
    FILE* file = fopen(filePath.c_str(), "a");
    std::string s = std::to_string(score);
    s.push_back(' ');
    fputs(s.c_str(), file);
    fclose(file);
}

FinalScreen::FinalScreen(SDL_Renderer* renderer, int score) {
    addScore(score - 4);
    showFinalScreen(renderer);
}

void FinalScreen::showFinalScreen(SDL_Renderer* renderer) {
    TTF_Init();
    TTF_Font* font1 = TTF_OpenFont(
            R"(C:\Users\micha\Documents\programming\code\cpp\labs\game_snake\content\fonts\font1.ttf)",
            40);
    TTF_Font* font2 = TTF_OpenFont(
            R"(C:\Users\micha\Documents\programming\code\cpp\labs\game_snake\content\fonts\font1.ttf)",
            60);

    std::vector<SDL_Rect> rects_1;
    std::vector<SDL_Rect> rects_2;
    std::vector<SDL_Texture*> textures_1;
    std::vector<SDL_Texture*> textures_2;
    std::vector<std::string> nicknames;
    std::vector<std::string> scores;

    // запись данных в вектора
    vectorRead(nicknames, scores);

    // согласованно сортируем вектора
    vectorSort(nicknames, scores);

    // готовим к рендеру ники и очки
    if (!nicknames.empty()) {
        prepareText(renderer, rects_1, rects_2, textures_1, textures_2, nicknames, scores, font1);
    }

    // готовим к рендеру заглавную надпись
    SDL_Rect rect_3;
    SDL_Texture* texture_3;
    get_text_and_rect(renderer, 310, 10, "Leaderboard", font2, &texture_3, &rect_3);

    // рендерим ники и очки на экран
    bool proceed = false;
    SDL_Event event;
    Input input;
    while (!proceed) {
        input.update(event);

        if (input.isKeyDown(SDLK_SPACE)) {
            proceed = true;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture_3, nullptr, &rect_3);
        if (!nicknames.empty()) {
            for (int i = 0; i < rects_1.size(); i++) {
                SDL_RenderCopy(renderer, textures_1[i], nullptr, &rects_1[i]);
                SDL_RenderCopy(renderer, textures_2[i], nullptr, &rects_2[i]);
            }
        }

        SDL_RenderPresent(renderer);
    }

    TTF_Quit();
}

void FinalScreen::vectorSort(std::vector<std::string>& nicknames, std::vector<std::string>& scores) {
    // сортировка с помощью вектора пар
    std::vector<std::pair<std::string, int>> temp_vec;
    for (int i = 0; i < nicknames.size(); ++i) {
        char const* temp_char = scores[i].c_str();
        int temp_int = atoi(temp_char);
        std::pair<std::string, int> temp_pair = {nicknames[i], temp_int};
        if (temp_int > 0) {
            temp_vec.push_back(temp_pair);
        }
    }
    sort(temp_vec.begin(), temp_vec.end(), sortByVal);

    // запись во временные вектора
    std::vector<std::string> temp_scores;
    std::vector<std::string> temp_nicknames;
    int cur_index = 0;
    int actual_index = 0;
    for (auto& iter: temp_vec) {
        bool skip = false;
        for (; cur_index > 0;) {
            --cur_index;
            if (temp_vec[cur_index].first == temp_vec[actual_index].first) {
                skip = true;
                break;
            }
            skip = false;
        }
        cur_index = actual_index;
        if (!skip) {
            temp_nicknames.push_back(iter.first);
            temp_scores.push_back(std::to_string(iter.second));
        }
        cur_index++;
        actual_index++;
    }

    // копирование временных векторов в основные
    scores.clear();
    nicknames.clear();
    if (!temp_nicknames.empty()) {
        std::copy(temp_scores.begin(), temp_scores.end(), std::back_inserter(scores));
        std::copy(temp_nicknames.begin(), temp_nicknames.end(), std::back_inserter(nicknames));
    }
    if (nicknames.size() > 10) {
        scores.resize(10);
        nicknames.resize(10);
    }
}

void FinalScreen::vectorRead(std::vector<std::string>& nicknames, std::vector<std::string>& scores) {
    std::string filePath_1 = R"(C:\Users\micha\Documents\programming\code\cpp\labs\game_snake\content\data\nicknames.txt)";
    std::string filePath_2 = R"(C:\Users\micha\Documents\programming\code\cpp\labs\game_snake\content\data\scores.txt)";
    FILE* file_1 = fopen(filePath_1.c_str(), "r");
    FILE* file_2 = fopen(filePath_2.c_str(), "r");

    // поочерёдно считываем ники
    while (true) {
        std::string nickname = " ";
        char temp_char;
        while (true) {
            temp_char = fgetc(file_1);
            if (temp_char == ' ' || temp_char == EOF) {
                break;
            } else if (nickname[0] == ' ') {
                nickname[0] = temp_char;
            } else {
                nickname.push_back(temp_char);
            }
        }
        if (temp_char == EOF) {
            break;
        } else {
            nicknames.push_back(nickname);
        }
    }

    // поочерёдно считываем очки
    while (true) {
        std::string score = " ";
        char temp_char;
        while (true) {
            temp_char = fgetc(file_2);
            if (temp_char == ' ' || temp_char == EOF) {
                break;
            } else if (score[0] == ' ') {
                score[0] = temp_char;
            } else {
                score.push_back(temp_char);
            }
        }
        if (temp_char == EOF) {
            break;
        } else {
            scores.push_back(score);
        }
    }

    fclose(file_1);
    fclose(file_2);
}

void FinalScreen::prepareText(SDL_Renderer* renderer, std::vector<SDL_Rect>& rects_1, std::vector<SDL_Rect>& rects_2,
                              std::vector<SDL_Texture*>& textures_1, std::vector<SDL_Texture*>& textures_2,
                              std::vector<std::string>& nicknames, std::vector<std::string>& scores, TTF_Font* font1) {
    SDL_Texture* texture_1;
    SDL_Texture* texture_2;
    SDL_Rect rect_1;
    SDL_Rect rect_2;
    int y = 100;
    for (int i = 0; i < nicknames.size(); i++) {
        textures_1.push_back(texture_1);
        textures_2.push_back(texture_2);
        rects_1.push_back(rect_1);
        rects_2.push_back(rect_2);
        get_text_and_rect(renderer, 10, y, nicknames[i], font1, &textures_1[i], &rects_1[i]);
        get_text_and_rect(renderer, 700, y, scores[i], font1, &textures_2[i], &rects_2[i]);
        y += 50;
    }
}

bool FinalScreen::sortByVal(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return (a.second > b.second);
}
