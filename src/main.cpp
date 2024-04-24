#include "include/game.hpp"

// Window Attributes
const int WIDTH = 1920;
const int HEIGHT = 1080;
const char *TITLE = "numb";

int main(int argc, const char *argv[])
{
    SetTraceLogLevel(LOG_ERROR);

    Game game;

    game.init(WIDTH, HEIGHT, TITLE);
    InitAudioDevice();
    game.startscreen();

    Textures exitsc;
    exitsc.load("assets/pages/exit.png");

    SetExitKey(KEY_NULL);
    bool exitWindowRequest{false}, exitWindow{false};

    SetTargetFPS(60);
    while (!exitWindow)
    {
        float dt = GetFrameTime();

        game.begin();
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE) || game.exit)
            exitWindowRequest = true;
        if (exitWindowRequest)
        {
            if (IsKeyPressed(KEY_Y))
                exitWindow = true;
            else if (IsKeyPressed(KEY_N))
            {
                exitWindowRequest = false;
                game.exit = false;
            }
        }

        if (exitWindowRequest)
        {
            DrawTexture(exitsc.getTexture(), 0, 0, WHITE);
        }
        else
        {
            game.update(dt);
        }
        game.end();
    }
    exitsc.unload();
    CloseAudioDevice();
    game.close();

    return 0;
}
