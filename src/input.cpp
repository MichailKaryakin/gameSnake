#include "input.h"

Input::Input() {
    this->exit = false;
}

void Input::Dispose() {
    this->_keyMap.clear();
    this->_previousKeyMap.clear();
}

Input::~Input() {
    Dispose();
}

// Цикл через _keyMap с использованием a для каждого цикла и скопировать его в _previousKeyMap
void Input::update(SDL_Event event) {
    for (auto& it: this->_keyMap) {
        this->_previousKeyMap[it.first] = it.second;
    }

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->exit = true;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    this->exit = true;
                    break;
                }
                pressKey(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                releaseKey(event.key.keysym.sym);
                break;
        }
    }
}

void Input::pressKey(unsigned int keyID) {
    this->_keyMap[keyID] = true;
    preLastKey = lastKey;
    lastKey = (char) keyID;
}

void Input::releaseKey(unsigned int keyID) {
    this->_keyMap[keyID] = false;
}

bool Input::isKeyDown(unsigned int keyID) {
    auto it = this->_keyMap.find(keyID);
    return it != this->_keyMap.end() && it->second;
}

char Input::getLastKey() const {
    return lastKey;
}

char Input::getPreLastKey() const {
    return preLastKey;
}

void Input::setPreLastKeyToInit() {
    preLastKey = ' ';
}
