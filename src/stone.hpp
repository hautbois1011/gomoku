#pragma once
#include <SDL2/SDL.h>

class Stone {
public:
    Stone(unsigned short x,
        unsigned short y,
        bool isBlack)
        : x(x), y(y), isBlack(isBlack) {
    }
    ~Stone();

    void update();
    void draw(SDL_Renderer*& renderer);

private:
    unsigned short x;
    unsigned short y;
    bool isBlack;
};
