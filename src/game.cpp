#include "include/game.hpp"

Game::Game()
{
    currLevel = -1;
}

Game::~Game()
{
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
    home = new Home();
    menu = new Menu();
}

void Game::begin()
{
    BeginDrawing();
    ClearBackground(WHITE);
}

void Game::update(float dt)
{
    if (tut)
    {
        DrawTexture(tutorial.getTexture(), 0, 0, WHITE);
        if (IsKeyPressed(KEY_T))
        {
            tut = false;
            tutorial.unload();
        }
        return;
    }
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
            tut = true;
            tutorial.load("assets/pages/tutorial.png");
        }
        else if (IsKeyPressed(KEY_E))
        {
            exit = true;
        }
        else if (IsKeyPressed(KEY_M))
        {
            mute = !mute;
        }
        break;
    case 0:
        home->render();
        home->update(dt);
        if (IsKeyPressed(KEY_P))
            currLevel = -1;

        if (IsKeyPressed(KEY_ENTER))
        {
            currLevel = home->pressed;
            switch (currLevel)
            {
            case 1:
                lvl1 = new Level1();
                break;
            case 2:
                lvl2 = new Level2();
                break;
            case 3:
                lvl3 = new Level3();
                break;
            case 4:
                lvl4 = new Level4();
                break;
            default:
                break;
            }
        }

        break;
    case 1:
        if (instruction[0])
        {
            lvl1->instr();
            if (IsKeyPressed(KEY_SPACE))
                instruction[0] = false;

            return;
        }
        lvl1->render();
        lvl1->update(dt);
        if (lvl1->complete())
        {
            if (home->currmap == 0)
                home->currmap = 1;
            currLevel = 0;
            delete lvl1;
        }

        break;
    case 2:
        if (instruction[1])
        {
            lvl2->instr();
            if (IsKeyPressed(KEY_SPACE))
                instruction[1] = false;

            return;
        }
        lvl2->render();
        lvl2->update(dt);
        if (lvl2->complete() && lvl2->getScore() >= 100)
        {
            if (home->currmap == 1)
                home->currmap = 2;
            currLevel = 0;
            delete lvl2;
        }
        else if (lvl2->complete() && lvl2->getScore() < 100)
        {
            currLevel = 0;
            delete lvl2;
        }

        break;
    case 3:
        if (instruction[2])
        {
            lvl3->instr();
            if (IsKeyPressed(KEY_SPACE))
                instruction[2] = false;

            return;
        }
        lvl3->render();
        lvl3->update(dt);
        if (lvl3->complete())
        {
            if (home->currmap == 2)
                home->currmap = 3;
            currLevel = 0;
            delete lvl3;
        }
        else if (lvl3->incomplete())
        {
            currLevel = 0;
            delete lvl3;
        }

        break;
    case 4:
        lvl4->render();
        if (lvl4->complete())
        {
            currLevel = 0;
            delete lvl4;
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