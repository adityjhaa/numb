#include "../include/game.hpp"

// Window Attributes
const int WIDTH = 1920;
const int HEIGHT = 1080;
const char *TITLE = "the_game";

const char *exitText = "Are you sure you want to exit program? [Y/N]";

int main(int argc, const char *argv[])
{
    SetTraceLogLevel(LOG_ERROR);

    Game game;

    game.init(WIDTH, HEIGHT, TITLE);
    InitAudioDevice();
    game.startscreen(TITLE);

    SetExitKey(KEY_NULL);
    bool exitWindowRequest{false}, exitWindow{false};

    SetTargetFPS(60);
    while (!exitWindow)
    {
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequest = true;
        if(exitWindowRequest)
        {
            if (IsKeyPressed(KEY_Y)) exitWindow = true;
            else if (IsKeyPressed(KEY_N)) exitWindowRequest = false;
        }

        game.begin();

        if(exitWindowRequest)
        {
            DrawRectangle(0, 400, WIDTH, 280, BLACK);
            DrawText(exitText, 240, 500, 60, LIGHTGRAY);
        }else{
            float dt = GetFrameTime();
            game.update(dt);
        }
        game.end();
    }
    game.close();
    CloseAudioDevice();

    return 0;
}
