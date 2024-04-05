#include "../include/game.hpp"

// Window Attributes
const int WIDHT = 1920;
const int HEIGHT = 1080;
const char *TITLE = "the_game";

int main(int argc, const char *argv[])
{
    Game game;

    SetTraceLogLevel(LOG_ERROR);

    game.initwindow(WIDHT, HEIGHT, TITLE);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        game.render();
    }
    return 0;
}