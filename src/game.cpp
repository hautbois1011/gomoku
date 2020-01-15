#include "game.hpp"
#include "board.hpp"
#include <iostream>
using namespace std;

GomokuGame::GomokuGame() {
    initSDL();
    mouse_pos = {0, 0};
    board = new Board();
}

GomokuGame::~GomokuGame() {
    cleanup();
    delete board;
}

//-------------------------------
// initialize SDL
//-------------------------------
int GomokuGame::initSDL() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "Initialization error: " << SDL_GetError() << endl;
        return 1;
    }

    window = SDL_CreateWindow(
            "Gomoku",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            SDL_WINDOW_SHOWN
            );

    if(!window) {
        cerr << "Window creation error: " << SDL_GetError() << endl;
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer) {
        cerr << "Renderer creation error: " << SDL_GetError() << endl;
        return 1;
    }

    running = true;

    return 0;
}

//-------------------------------
// clean up
//-------------------------------
void GomokuGame::cleanup() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

//-------------------------------
// event polling
//-------------------------------
void GomokuGame::event() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
            // cout << "x: " << mouse_pos.x << " y: " << mouse_pos.y << endl;
            break;
        default:
            break;
        }
    }
}

//-------------------------------
// update datas
//-------------------------------
void GomokuGame::update() {}

//-------------------------------
// drawing
//-------------------------------
void GomokuGame::draw() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    board->draw(renderer, mouse_pos);

    SDL_RenderPresent(renderer);
}
