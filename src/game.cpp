#include "../include/game.hpp"

Game::Game() {}

Game::~Game() {}

void Game::initwindow(int width, int height, const char *title)
{
    InitWindow(width, height, title);
}

void Game::draw()
{
}

void Game::render()
{
    BeginDrawing();
    ClearBackground(WHITE);

    Game::draw();

    EndDrawing();
}