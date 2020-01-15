#pragma once
#include <SDL2/SDL.h>

class Board {
public:
    Board();
    ~Board();

    void update();
    void draw(SDL_Renderer*& renderer);
private:
    const unsigned short BOARD_X = 13;
    const unsigned short BOARD_Y = 13;
    const unsigned short OFFSET_X = 50;
    const unsigned short OFFSET_Y = 50;
    const unsigned short GRID_SIZE = 30;
};
