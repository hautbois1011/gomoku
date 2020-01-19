#include <SDL2/SDL.h>
#include <vector>
#include "board.hpp"
#include "stone.hpp"

Board::Board() {
}

Board::~Board() {
}

//---------------------------------
// update data
//---------------------------------
void Board::update() {}

//---------------------------------
// drawing board
//---------------------------------
void Board::draw(SDL_Renderer*& renderer, const SDL_Point& mouse_pos) {
    // draw mouse over highlight
    short x = (mouse_pos.x - OFFSET_X + GRID_SIZE / 2) / GRID_SIZE;
    short y = (mouse_pos.y - OFFSET_Y + GRID_SIZE / 2) / GRID_SIZE;

    if(x >= 0 && y >= 0 && x < BOARD_X && y < BOARD_Y) {
        SDL_Rect highlight = {
            OFFSET_X - GRID_SIZE / 2 + x * GRID_SIZE,
            OFFSET_Y - GRID_SIZE / 2 + y * GRID_SIZE,
            GRID_SIZE,
            GRID_SIZE
        };

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &highlight);
    }

    // draw board
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
