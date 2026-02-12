#pragma once

#include <SDL.h>
#include <unordered_map>
#include <vector>

class Input {
public:
    Input();

    ~Input();

    void update(SDL_Event event);

    void Dispose();

    void pressKey(unsigned int keyID);

    void releaseKey(unsigned int keyID);

    // возвращает true, если клавиша нажата
    bool isKeyDown(unsigned int keyID);

    char getLastKey() const;

    char getPreLastKey() const;

    void setPreLastKeyToInit();

    bool exit;
private:
    char lastKey = ' ';
    char preLastKey = ' ';
    std::unordered_map<unsigned int, bool> _keyMap;
    std::unordered_map<unsigned int, bool> _previousKeyMap;
};
