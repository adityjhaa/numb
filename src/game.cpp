#include "../include/game.hpp"

Game::Game() {}

Game::~Game()
{
    player = nullptr;
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
    loadplayer();
}

void Game::loadplayer()
{
    player = new Character("assets/main_char/Idle.png", "assets/main_char/Run.png");
    player->initchar(Vector2{100.f, 100.f}, 0, 1.0 / 12.0, 0.f);
}

void Game::render()
{
    BeginDrawing();
    ClearBackground(WHITE);
}

void Game::update(float dt)
{
    player->updatechar(dt);
}

void Game::end()
{
    EndDrawing();
}

void Game::close()
{
    CloseWindow();
}