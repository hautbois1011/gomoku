#include "game.hpp"
#include "board.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

GomokuGame::GomokuGame() {
    initSDL();
    mouse_pos = {0, 0};
    board = new Board();
    stones = std::vector<Stone>();
    turnIsBlack = true;
    gameEnd = false;

    table = std::vector<std::vector<COLOR>>(
        BOARD_Y,
        std::vector<COLOR>(BOARD_X, NONE)
    );
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

        case SDL_MOUSEBUTTONDOWN:
            if(gameEnd) {
                break;
            }

            {
                short x = (mouse_pos.x - OFFSET_X + GRID_SIZE / 2) / GRID_SIZE;
                short y = (mouse_pos.y - OFFSET_Y + GRID_SIZE / 2) / GRID_SIZE;
                // cout << "x: " << x << " y: " << y << endl;

                const Stone s = Stone(x, y, true);
                if(std::find(stones.begin(), stones.end(), s) == stones.end()
                        || stones.empty()) {
                    stones.push_back(Stone(x, y, turnIsBlack));
                    table[y][x] = turnIsBlack ? BLACK : WHITE;

                    for(auto ity = table.begin(); ity != table.end(); ity++) {
                        for(auto itx = ity->begin(); itx != ity->end(); itx++) {
                            cout << *itx << " ";
                        }
                        cout << endl;
                    }

                    cout << "--------------------------" << endl;

                    std::vector<short> rep;                    

                    for(auto vec = VECS.begin(); vec != VECS.end(); vec++) {
                        short xx = (*vec)[0];
                        short yy = (*vec)[1];
                        short count = 0;

                        while(x + xx < BOARD_X && y + yy < BOARD_Y
                            && x + xx >= 0 && y + yy >= 0
                            && table[y + yy][x + xx] == (turnIsBlack ? BLACK : WHITE)) {
                            // cout << "x+xx: " << x+xx << " y+yy: " << y+yy <<endl;
                            xx += (*vec)[0];
                            yy += (*vec)[1];
                            count++;
                        }
                        // cout << xx << " " << yy << endl;
                        // cout << count << endl;
                        rep.push_back(count);
                    }

                    cout << "\\: " << rep[0] + rep[7] << endl;
                    cout << "-: " << rep[1] + rep[6] << endl;
                    cout << "/: " << rep[2] + rep[5] << endl;
                    cout << "|: " << rep[3] + rep[4] << endl;

                    cout << "--------------------------" << endl;

                    if(    rep[0] + rep[7] >= 4
                        || rep[1] + rep[6] >= 4
                        || rep[2] + rep[5] >= 4
                        || rep[3] + rep[4] >= 4) {
                        cout << "game end!" << endl;
                        gameEnd = true;
                    }

                    turnIsBlack = !turnIsBlack;
                }
                break;
            }

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
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);

    board->draw(renderer, mouse_pos);

    // draw stones
    for(auto it = stones.begin(); it != stones.end(); it++) {
        it->draw(renderer);
    }

    SDL_RenderPresent(renderer);
}
