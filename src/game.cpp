#include "../include/game.hpp"

Game::Game() {}

Game::~Game()
{
    lvl1 = nullptr;
    lvl2 = nullptr;
}

void Game::init(int width, int height, const char *title)
{
    InitWindow(width, height, title);
}

void Game::startscreen(const char *name)
{
    bool startplay{false};
    while ((!startplay) && (!WindowShouldClose()))
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(name, 780, 460, 80, YELLOW);

        DrawText("<SPACE> to PLAY", 775, 800, 40, RED);
        if (IsKeyPressed(KEY_SPACE))
        {
            startplay = true;
        }
        EndDrawing();
    }
    // lvl1 = new Level1();
    lvl2 = new Level2();

}

void Game::update(float dt)
{
    // lvl1->render();
    // lvl1->update(dt);
    lvl2->render();
    lvl2->update(dt);
}

void Game::end()
{
    EndDrawing();
}

void Game::close()
{
    CloseWindow();
}