#include "../include/game.hpp"

// Window Attributes
const int WIDHT = 1920;
const int HEIGHT = 1080;
const char *TITLE = "the_game";

int main(int argc, const char *argv[])
{
    Game game;

    SetTraceLogLevel(LOG_ERROR);

    game.init(WIDHT, HEIGHT, TITLE);
    game.startscreen(TITLE);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        game.update(dt);
        game.end();
    }
    game.close();

    return 0;
}