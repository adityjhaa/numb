#pragma once

#include "SDL2/SDL.h"

class Game
{

    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    Game();
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();
};
