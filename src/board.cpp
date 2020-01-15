#include <SDL2/SDL.h>
#include "board.hpp"

Board::Board() {}
Board::~Board() {}

//---------------------------------
// update data
//---------------------------------
void Board::update() {}

//---------------------------------
// drawing board
//---------------------------------
void Board::draw(SDL_Renderer*& renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for(int i = 0; i < BOARD_X; i++) {
        SDL_RenderDrawLine(
            renderer,
            OFFSET_X + GRID_SIZE * i,
            OFFSET_Y,
            OFFSET_X + GRID_SIZE * i,
            OFFSET_Y + GRID_SIZE * (BOARD_Y - 1)
        );
    }

    for(int i = 0; i < BOARD_Y; i++) {
        SDL_RenderDrawLine(
            renderer,
            OFFSET_X,
            OFFSET_Y + GRID_SIZE * i,
            OFFSET_X + GRID_SIZE * (BOARD_X - 1),
            OFFSET_Y + GRID_SIZE * i
        );
    }
}
