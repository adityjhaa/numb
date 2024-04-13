#include "../include/game.hpp"

#define PGREEN \
    (Color) { 150, 255, 30, 255 }

Game::Game()
{
    currLevel = 0;
}

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
    bool start{false};
    while ((!start) && (!WindowShouldClose()))
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(name, 848, 460, 80, PGREEN);

        DrawText("<SPACE>", 870, 800, 40, RED);
        if (IsKeyPressed(KEY_SPACE))
        {
            start = true;
        }
        EndDrawing();
    }
    lvl1 = new Level1();
    lvl2 = new Level2();
    currLevel = 1;
}

void Game::begin()
{
    BeginDrawing();
    ClearBackground(WHITE);
}

void Game::update(float dt)
{
    switch (currLevel)
    {
    case 1:
        lvl1->render();
        lvl1->update(dt);
        if (lvl1->complete())
            currLevel++;

        break;
    case 2:
        lvl2->render();
        lvl2->update(dt);
        if (lvl2->complete())
            currLevel++;

        break;
    default:
        break;
    }
}

void Game::end()
{
    EndDrawing();
}

void Game::close()
{
    CloseWindow();
}