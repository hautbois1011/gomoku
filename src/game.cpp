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

    if(TTF_Init() != 0) {
        cerr << "TTF Initialization error: " << TTF_GetError() << endl;
    }

    font = TTF_OpenFont("../font/RictyDiminished-Regular.ttf", 30);

    if(!font) {
        cerr << "Font opening error: " << endl;
    }

    surface = TTF_RenderUTF8_Blended(
        font,
        "Turn: Black",
        (SDL_Color){0, 0, 0, 255}
    );
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    int flags = MIX_INIT_MOD;
    int initted = Mix_Init(flags);
    if((initted & flags) != flags) {
        cerr << "SDL Mixer initialization error: " << Mix_GetError() << endl;
    }

    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        cerr << "Opening audio error: " << Mix_GetError() << endl;
    }

    music = Mix_LoadMUS("../sound/gomoku_bgm.wav");
    if(!music) {
        cerr << "Cannot load gomoku_bgm.mp3" << endl;
    }

    Mix_PlayMusic(music, -1);

    running = true;

    return 0;
}

//-------------------------------
// clean up
//-------------------------------
void GomokuGame::cleanup() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_Quit();

    TTF_CloseFont(font);
    TTF_Quit();

    Mix_CloseAudio();
    Mix_Quit();
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

            if(judge()) {
                gameEnd = true;

                surface = TTF_RenderUTF8_Blended(
                        font,
                        "Game Over",
                        (SDL_Color){0, 0, 0, 255}
                        );
                texture = SDL_CreateTextureFromSurface(renderer, surface);
                break;
            }


            if(turnIsBlack) {
                surface = TTF_RenderUTF8_Blended(
                        font,
                        "Turn: Black",
                        (SDL_Color){0, 0, 0, 255}
                        );
            } else {
                surface = TTF_RenderUTF8_Blended(
                        font,
                        "Turn: White",
                        (SDL_Color){0, 0, 0, 255}
                        );
            }
            texture = SDL_CreateTextureFromSurface(renderer, surface);

            break;

        default:
            break;
        }
    }
}

//-----------------------------
// put stone and judge whether ending
//-----------------------------
bool GomokuGame::judge() {
    short x = (mouse_pos.x - OFFSET_X + GRID_SIZE / 2) / GRID_SIZE;
    short y = (mouse_pos.y - OFFSET_Y + GRID_SIZE / 2) / GRID_SIZE;
    // cout << "x: " << x << " y: " << y << endl;

    const Stone s = Stone(x, y, true);
    if(std::find(stones.begin(), stones.end(), s) == stones.end()
            || stones.empty()) {
        stones.push_back(Stone(x, y, turnIsBlack));
        table[y][x] = turnIsBlack ? BLACK : WHITE;

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

        // toggle player
        turnIsBlack = !turnIsBlack;

        return (rep[0] + rep[7] >= 4
             || rep[1] + rep[6] >= 4
             || rep[2] + rep[5] >= 4
             || rep[3] + rep[4] >= 4);
    }
    return false;
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

    int iw, ih;
    SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);

    SDL_Rect txtRect = (SDL_Rect){0, 0, iw, ih};
    SDL_Rect pasteRect = (SDL_Rect){430, 100, iw, ih};

    SDL_RenderCopy(renderer, texture, &txtRect, &pasteRect);

    board->draw(renderer, mouse_pos);

    // draw stones
    for(auto it = stones.begin(); it != stones.end(); it++) {
        it->draw(renderer);
    }

    SDL_RenderPresent(renderer);
}
