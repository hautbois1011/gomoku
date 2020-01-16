#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "stone.hpp"

const short BOARD_X = 13;
const short BOARD_Y = 13;
const short OFFSET_X = 50;
const short OFFSET_Y = 50;
const short GRID_SIZE = 30;

class Board {
public:
    Board();
    ~Board();

    void update();
    void draw(SDL_Renderer*& renderer, const SDL_Point& mouse_pos);

private:
};
