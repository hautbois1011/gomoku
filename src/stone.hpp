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

    bool operator==(const Stone rhs) const {
        return (this->x == rhs.x && this->y == rhs.y);
    }

    void update();
    void draw(SDL_Renderer*& renderer);

private:
    unsigned short x;
    unsigned short y;
    bool isBlack;
};
