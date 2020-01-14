#include <SDL2/SDL.h>

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
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
};