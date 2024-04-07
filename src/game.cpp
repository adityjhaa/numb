#include "../include/game.hpp"

Game::Game() {}

Game::~Game()
{
    map = nullptr;
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
    loadmap();
    loadplayer();
}

void Game::loadplayer()
{
    player = new Character("assets/main_char/Idle.png", "assets/main_char/Run.png");
    player->initchar(Vector2{250.f, 250.f}, 0, 1.0 / 15.0, 0.f);
}

void Game::loadmap()
{
    map = new Map("assets/map.png");
}

void Game::render()
{
    movecamera = player->movecamera();
    movecamera.first ? cameramovement.first = 1 : cameramovement.first = 0;
    movecamera.second ? cameramovement.second = 1 : cameramovement.second = 0;

    BeginDrawing();
    ClearBackground(WHITE);

    camx = (player->getpos().x - 896.f) * cameramovement.first;
    camy = (player->getpos().y - 476.f) * cameramovement.second;

    if (!movecamera.first and (player->getpos().x > 1000.f))
    {
        camx = 1920.f;
    }
    if (!movecamera.second and (player->getpos().y > 1000.f))
    {
        camy = 2760.f;
    }

    map->drawmap(Vector2{camx, camy});
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