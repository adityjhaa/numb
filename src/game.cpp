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
    loadmap();
    loadplayer();
}

void Game::loadplayer()
{
    player = new Character("assets/main_char/Idle.png", "assets/main_char/Run.png");
    player->initchar(Vector2{896.f, 476.f}, 0, 1.0 / 15.0, 0.f);
}

void Game::loadmap()
{
    map.load("assets/map.png");
    mapsrc= {0, 0, (float)map.getTexture().width, (float)map.getTexture().height};
    mapdest = {0, 0, (float)map.getTexture().width* 2, (float)map.getTexture().height * 2};
}

void Game::render()
{
    BeginDrawing();
    ClearBackground(WHITE);
    DrawTexturePro(map.getTexture(), mapsrc, mapdest, Vector2{player->getpos().x - 960.f, player->getpos().y - 540.f}, 0.0, WHITE);
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
    map.unload();
    CloseWindow();
}