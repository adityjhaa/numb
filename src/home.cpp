#include "include/home.hpp"

Home::Home()
{
    loadplayer();
    loadmaps();
}

Home::~Home()
{
    delete player;
    delete map;
    player = nullptr;
    map = nullptr;
    unloadmaps();
}

void Home::loadplayer()
{
    player = new Character("assets/main_char/Idle.png", "assets/main_char/Run.png");
    player->initchar(Vector2{46.f, 830.f}, 0, 1.0 / 15.0, 0.f);
}

void Home::loadmaps()
{
    doors[0].load("assets/maps/mdr/map01.png");
    doors[1].load("assets/maps/mdr/map02.png");
    doors[2].load("assets/maps/mdr/map03.png");
    doors[3].load("assets/maps/mdr/map04.png");
}

void Home::unloadmaps()
{
    for (auto d : doors)
        d.unload();
}

void Home::updatechar(float dt)
{
    if (IsKeyDown(KEY_A))
        player->vel.x = -1.0;
    if (IsKeyDown(KEY_D))
        player->vel.x = 1.0;

    if (Vector2Length(player->vel) != 0.0)
    {
        player->pos = Vector2Add(player->pos, Vector2Scale(Vector2Normalize(player->vel), player->speed));

        (player->vel.x < 0.f) ? player->right_left = -1.f : player->right_left = 1.f;

        player->texture = player->run;
        player->maxframes = 12;
    }
    else
    {
        player->texture = player->idle;
        player->maxframes = 11;
    }
    player->vel = {};

    player->runningTime += dt;
    if (player->runningTime >= player->updateTime)
    {
        player->runningTime = 0.f;
        player->frame++;
        player->frame = player->frame % player->maxframes;
    }

    if (player->pos.x < -64.f)
        player->pos.x = -64.f;
    if (player->pos.x > 1856.f)
        player->pos.x = 1856.f;

    Rectangle source{player->frame * player->width, 0.f, player->right_left * player->width, player->height};
    Rectangle dest{player->pos.x, player->pos.y, player->scale * player->width, player->scale * player->height};
    DrawTexturePro(player->texture.getTexture(), source, dest, Vector2{}, 0.f, WHITE);
}

void Home::render()
{
    DrawTexture(doors[currmap].getTexture(), 0, 0, WHITE);
}

void Home::update(float dt)
{
    updatechar(dt);
    entries();
}

void Home::entries()
{
    if (player->pos.x > 200.f and player->pos.x < 400.f)
    {
        DrawText("Level 1 : <ENTER>", 30.f, 25.f, 60, WHITE);
        pressed = 1;
        return;
    }

    if (player->pos.x > 600.f and player->pos.x < 800.f and currmap > 0)
    {
        DrawText("Level 2 : <ENTER>", 30.f, 25.f, 60, WHITE);
        pressed = 2;
        return;
    }

    if (player->pos.x > 1000.f and player->pos.x < 1200.f and currmap > 1)
    {
        DrawText("Level 3 : <ENTER>", 30.f, 25.f, 60, WHITE);
        pressed = 3;
        return;
    }

    if (player->pos.x > 1400.f and player->pos.x < 1600.f and currmap > 2)
    {
        DrawText("Level 4 : <ENTER>", 30.f, 25.f, 60, WHITE);
        pressed = 4;
        return;
    }

    DrawText("Menu : <P>", 30.f, 25.f, 60, WHITE);

    pressed = 0;
}
