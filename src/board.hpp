#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "stone.hpp"

class Board {
public:
    Board();
    ~Board();

    void update();
    void draw(SDL_Renderer*& renderer, const SDL_Point& mouse_pos);

private:
    const unsigned short BOARD_X = 13;
    const unsigned short BOARD_Y = 13;
    const unsigned short OFFSET_X = 50;
    const unsigned short OFFSET_Y = 50;
    const unsigned short GRID_SIZE = 30;

    std::vector<Stone>* stones;
};
