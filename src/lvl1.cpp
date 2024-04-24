#include "include/lvl1.hpp"

Level1::Level1()
{
    loadinstr();
    loadplayer();
    loadmap();
    addcolliders();
    s = LoadSound("assets/sounds/nothing.mp3");
}

Level1::~Level1()
{
    instpage.unload();
    delete player;
    delete map;
    player = nullptr;
    map = nullptr;
    UnloadSound(s);
}

void Level1::loadmap()
{
    map = new Map("assets/maps/map1.png", 1.f);
}

void Level1::updatechar(float dt)
{

    if ((player->pos.x > 2950.f) and (player->pos.y > 3300.f))
    {
        finish = true;
        if (first)
            PlaySound(s);

        first = false;
    }

    player->lastframe = player->pos;
    if (IsKeyDown(KEY_A))
        player->vel.x = -1.0;
    if (IsKeyDown(KEY_S))
        player->vel.y = 1.0;
    if (IsKeyDown(KEY_D))
        player->vel.x = 1.0;
    if (IsKeyDown(KEY_W))
        player->vel.y = -1.0;

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
    player->vel = {};

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

    Rectangle source{player->frame * player->width, 0.f, player->right_left * player->width, player->height};
    Rectangle dest{player->xpos, player->ypos, player->scale * player->width, player->scale * player->height};
    DrawTexturePro(player->texture.getTexture(), source, dest, Vector2{}, 0.0, WHITE);
}

void Level1::addcolliders()
{
    colliders.push_back(Rectangle{192.f, 192.f, 704.f, 64.f});
    colliders.push_back(Rectangle{192.f, 256.f, 64.f, 1024.f});
    colliders.push_back(Rectangle{832.f, 256.f, 64.f, 384.f});
    colliders.push_back(Rectangle{256.f, 1216.f, 384.f, 64.f});
    colliders.push_back(Rectangle{640.f, 640.f, 2560.f, 64.f});
    colliders.push_back(Rectangle{640.f, 704.f, 64.f, 192.f});
    colliders.push_back(Rectangle{1024.f, 704.f, 64.f, 192.f});
    colliders.push_back(Rectangle{640.f, 1024.f, 64.f, 2176.f});
    colliders.push_back(Rectangle{3136.f, 704.f, 64.f, 2496.f});
    colliders.push_back(Rectangle{704.f, 3136.f, 2112.f, 64.f});
    colliders.push_back(Rectangle{2944.f, 3136.f, 192.f, 64.f});
    colliders.push_back(Rectangle{704.f, 1024.f, 192.f, 64.f});
    colliders.push_back(Rectangle{832.f, 832.f, 64.f, 192.f});
    colliders.push_back(Rectangle{1024.f, 1024.f, 256.f, 64.f});
    colliders.push_back(Rectangle{1216.f, 832.f, 64.f, 192.f});
    colliders.push_back(Rectangle{1280.f, 832.f, 384.f, 64.f});
    colliders.push_back(Rectangle{1792.f, 704.f, 64.f, 192.f});
    colliders.push_back(Rectangle{1600.f, 896.f, 64.f, 448.f});
    colliders.push_back(Rectangle{1664.f, 1024.f, 320.f, 64.f});
    colliders.push_back(Rectangle{1984.f, 832.f, 64.f, 512.f});
    colliders.push_back(Rectangle{2048.f, 832.f, 192.f, 64.f});
    colliders.push_back(Rectangle{2176.f, 896.f, 64.f, 1472.f});
    colliders.push_back(Rectangle{2368.f, 704.f, 64.f, 384.f});
    colliders.push_back(Rectangle{2752.f, 704.f, 64.f, 128.f});
    colliders.push_back(Rectangle{2560.f, 832.f, 448.f, 64.f});
    colliders.push_back(Rectangle{2240.f, 1216.f, 320.f, 64.f});
    colliders.push_back(Rectangle{2560.f, 896.f, 64.f, 768.f});
    colliders.push_back(Rectangle{2944.f, 896.f, 64.f, 1984.f});
    colliders.push_back(Rectangle{2944.f, 3008.f, 64.f, 128.f});
    colliders.push_back(Rectangle{3200.f, 3008.f, 384.f, 64.f});
    colliders.push_back(Rectangle{2688.f, 3200.f, 64.f, 384.f});
    colliders.push_back(Rectangle{3584.f, 3008.f, 64.f, 640.f});
    colliders.push_back(Rectangle{2688.f, 3584.f, 896.f, 64.f});
    colliders.push_back(Rectangle{832.f, 1216.f, 448.f, 64.f});
    colliders.push_back(Rectangle{832.f, 1280.f, 64.f, 448.f});
    colliders.push_back(Rectangle{1216.f, 1280.f, 64.f, 448.f});
    colliders.push_back(Rectangle{1408.f, 1024.f, 64.f, 512.f});
    colliders.push_back(Rectangle{1024.f, 1408.f, 64.f, 448.f});
    colliders.push_back(Rectangle{704.f, 1856.f, 576.f, 64.f});
    colliders.push_back(Rectangle{1280.f, 1664.f, 192.f, 64.f});
    colliders.push_back(Rectangle{832.f, 1920.f, 64.f, 576.f});
    colliders.push_back(Rectangle{896.f, 2240.f, 384.f, 64.f});
    colliders.push_back(Rectangle{896.f, 2432.f, 192.f, 64.f});
    colliders.push_back(Rectangle{704.f, 2624.f, 192.f, 64.f});
    colliders.push_back(Rectangle{1472.f, 1472.f, 576.f, 64.f});
    colliders.push_back(Rectangle{1792.f, 1216.f, 64.f, 256.f});
    colliders.push_back(Rectangle{1600.f, 1536.f, 64.f, 256.f});
    colliders.push_back(Rectangle{1024.f, 2048.f, 384.f, 64.f});
    colliders.push_back(Rectangle{1408.f, 1728.f, 64.f, 768.f});
    colliders.push_back(Rectangle{1600.f, 1536.f, 64.f, 256.f});
    colliders.push_back(Rectangle{1792.f, 1664.f, 64.f, 640.f});
    colliders.push_back(Rectangle{1984.f, 1536.f, 64.f, 576.f});
    colliders.push_back(Rectangle{1856.f, 2048.f, 128.f, 64.f});
    colliders.push_back(Rectangle{1856.f, 2240.f, 192.f, 64.f});
    colliders.push_back(Rectangle{2368.f, 1408.f, 64.f, 384.f});
    colliders.push_back(Rectangle{1472.f, 1920.f, 320.f, 64.f});
    colliders.push_back(Rectangle{2368.f, 1792.f, 384.f, 64.f});
    colliders.push_back(Rectangle{2752.f, 1024.f, 64.f, 1216.f});
    colliders.push_back(Rectangle{2816.f, 1216.f, 128.f, 64.f});
    colliders.push_back(Rectangle{2240.f, 1984.f, 384.f, 64.f});
    colliders.push_back(Rectangle{1600.f, 2112.f, 64.f, 512.f});
    colliders.push_back(Rectangle{1664.f, 2432.f, 192.f, 64.f});
    colliders.push_back(Rectangle{1216.f, 2432.f, 192.f, 64.f});
    colliders.push_back(Rectangle{1280.f, 2432.f, 192.f, 64.f});
    colliders.push_back(Rectangle{1024.f, 2496.f, 64.f, 320.f});
    colliders.push_back(Rectangle{1216.f, 2496.f, 64.f, 512.f});
    colliders.push_back(Rectangle{832.f, 2816.f, 256.f, 64.f});
    colliders.push_back(Rectangle{832.f, 2880.f, 64.f, 128.f});
    colliders.push_back(Rectangle{1024.f, 3008.f, 64.f, 128.f});
    colliders.push_back(Rectangle{1408.f, 2624.f, 448.f, 64.f});
    colliders.push_back(Rectangle{1408.f, 2688.f, 64.f, 320.f});
    colliders.push_back(Rectangle{1600.f, 2816.f, 64.f, 320.f});
    colliders.push_back(Rectangle{1792.f, 2688.f, 64.f, 448.f});
    colliders.push_back(Rectangle{1984.f, 2304.f, 64.f, 704.f});
    colliders.push_back(Rectangle{2048.f, 2496.f, 128.f, 64.f});
    colliders.push_back(Rectangle{2176.f, 2496.f, 64.f, 128.f});
    colliders.push_back(Rectangle{2176.f, 2624.f, 256.f, 64.f});
    colliders.push_back(Rectangle{2176.f, 2880.f, 64.f, 256.f});
    colliders.push_back(Rectangle{2368.f, 2688.f, 64.f, 256.f});
    colliders.push_back(Rectangle{2368.f, 2944.f, 256.f, 64.f});
    colliders.push_back(Rectangle{2432.f, 2176.f, 320.f, 64.f});
    colliders.push_back(Rectangle{2368.f, 2176.f, 64.f, 320.f});
    colliders.push_back(Rectangle{2560.f, 2368.f, 256.f, 64.f});
    colliders.push_back(Rectangle{2560.f, 2432.f, 64.f, 512.f});
    colliders.push_back(Rectangle{2624.f, 2560.f, 320.f, 64.f});
    colliders.push_back(Rectangle{2752.f, 2752.f, 64.f, 384.f});
}

bool Level1::complete()
{
    return (finish and IsKeyPressed(KEY_SPACE));
}

void Level1::loadinstr()
{
    instpage.load("assets/pages/instr1.png");
}

void Level1::instr()
{
    DrawTexture(instpage.getTexture(), 0, 0, WHITE);
}