#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "board.hpp"

class GomokuGame {
public:
    int Main() {
        while(running) {
            event();
            update();
            draw();
        }

        return 0;
    }

    GomokuGame();
    ~GomokuGame();

    // initialize SDL
    int initSDL();
    // clean up
    void cleanup();
    // event polling
    void event();
    // update datas
    void update();
    // drawing
    void draw();

private:
    bool judge();

private:
    enum COLOR {
        NONE,
        BLACK,
        WHITE
    };

    const std::vector<std::vector<short> > VECS = {
        {1, 1},
        {1, 0},
        {1, -1},
        {0, 1},
        {0, -1},
        {-1, 1},
        {-1, 0},
        {-1, -1}
    };

    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    TTF_Font* font;
    Mix_Music* music;

    SDL_Point mouse_pos;
    bool turnIsBlack;
    bool gameEnd;

    std::vector<Stone> stones;

    // count repetation of same color
    std::vector<std::vector<COLOR> > table;

    Board* board;
};
