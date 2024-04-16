#include "../include/game.hpp"

Game::Game()
{
    currLevel = -1;
}

Game::~Game()
{
    menu = nullptr;
    home = nullptr;
    lvl1 = nullptr;
    lvl2 = nullptr;
}

void Game::init(int width, int height, const char *title)
{
    InitWindow(width, height, title);
}

void Game::startscreen()
{
    bool start{false};
    Textures startsc;
    startsc.load("assets/pages/start.png");
    while ((!start) && (!WindowShouldClose()))
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(startsc.getTexture(), 0, 0, WHITE);
        if (IsKeyPressed(KEY_SPACE))
        {
            start = true;
        }
        EndDrawing();
    }
    startsc.unload();
    menu = new Menu();
    home = new Home();
    lvl1 = new Level1();
    lvl2 = new Level2();
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
    case -1:
        menu->render();
        menu->update(dt);

        if (IsKeyPressed(KEY_P))
        {
            currLevel = 0;
        }
        else if (IsKeyPressed(KEY_T))
        {
            // turtorial
        }
        else if (IsKeyPressed(KEY_E))
        {
            // exit
        }
        else if (IsKeyPressed(KEY_M))
        {
            // mute
        }
        break;
    case 0:
        home->render();
        home->update(dt);
        if (IsKeyPressed(KEY_P))
            currLevel = -1;

        break;

    case 1:
        if (instruction)
        {
            lvl1->instr();
            if (IsKeyPressed(KEY_SPACE))
                instruction = false;

            return;
        }
        lvl1->render();
        lvl1->update(dt);
        if (lvl1->complete())
        {
            home->currmap++;
            currLevel = 0;
            instruction = false;
        }

        break;
    case 2:
        lvl2->render();
        lvl2->update(dt);
        if (lvl2->complete())
        {
            home->currmap++;
            currLevel = 0;
            instruction = false;
        }

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