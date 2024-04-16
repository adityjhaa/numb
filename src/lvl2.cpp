#include "../include/lvl2.hpp"

Level2::Level2()
{
    loadplayer();
    loadmap();
    floor = Floor((char*)"ssets/maps/floor/Goodfloor.png");
}

Level2::~Level2()
{
    player = nullptr;
    map = nullptr;
}

void Level2::loadmap()
{
    map = new Map("assets/maps/map2.png", 4.f);
}

void Level2::updatechar(float dt)
{
    player->vel.y += .05;
    player->lastframe = player->pos;
    if (IsKeyDown(KEY_A))
        player->vel.x = -1.0;
    if (IsKeyDown(KEY_D))
        player->vel.x = 1.0;
    if (IsKeyPressed(KEY_SPACE))
        player->vel.y = -1.f;

    if (IsKeyReleased(KEY_A) || IsKeyReleased(KEY_D))
        player->vel = {};

    if (Vector2Length(player->vel) != 0.0)
    {
        player->pos = Vector2Add(player->pos, Vector2Scale(Vector2Normalize(player->vel), player->speed));

        if (player->vel.x < 0.f)
            player->right_left = -1.f;
        else if (player->vel.x > 0.f)
            player->right_left = 1.f;

        player->texture = player->run;
        player->maxframes = 12;
    }
    else
    {
        player->texture = player->idle;
        player->maxframes = 11;
    }

    player->runningTime += dt;
    if (player->runningTime >= player->updateTime)
    {
        player->runningTime = 0.f;
        player->frame++;
        player->frame = player->frame % player->maxframes;
    }

    (player->pos.x >= 896.f and player->pos.x <= 2816.f) ? player->shouldstay.first = true : player->shouldstay.first = false;
    (player->pos.y >= 476.f and player->pos.y <= 3236.f) ? player->shouldstay.second = true : player->shouldstay.second = false;

    player->shouldstay.first ? player->xpos = 896.f : player->xpos = player->pos.x;
    player->shouldstay.second ? player->ypos = 476.f : player->ypos = player->pos.y;

    if (player->pos.x > 2816.f)
        player->xpos = player->pos.x - 1920;

    if (player->pos.y > 3236.f)
        player->ypos = player->pos.y - 2760;

    floor.draw();
    Rectangle source{player->frame * player->width, 0.f, player->right_left * player->width, player->height};
    Rectangle dest{player->xpos, player->ypos, player->scale * player->width, player->scale * player->height};
    DrawTexturePro(player->texture.getTexture(), source, dest, Vector2{}, 0.0, WHITE);
}


void Level2::addcolliders() {}

bool Level2::complete() { return false; }