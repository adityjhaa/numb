#include "../include/lvl3.hpp"

Level3::Level3()
{
    loadinstr();
    loadmap();
    loadplayer();
    addcolliders();
    s = LoadSound("");
}

Level3::~Level3()
{
    instpage.unload();
    player = nullptr;
    map1 = map2 = nullptr;
    UnloadSound(s);
}

void Level3::loadplayer()
{
    const char *path1 = "assets/main_char/Idle.png";
    const char *path2 = "assets/main_char/Run.png";
    const char *path3 = "assets/main_char/Jump.png";
    const char *path4 = "assets/main_char/Fall.png";
    const char *path5 = "assets/main_char/Double_Jump.png";
    const char *path6 = "assets/main_char/Hit.png";

    player = new Character(path1, path2, path3, path4, path5, path6);
    player->initchar(Vector2{20.f, 592.f}, 0, 1.0 / 15.0, 0.f);
}

void Level3::loadmap()
{
    map1 = new Map("assets/maps/map31.png", 4.f);
    map2 = new Map("assets/maps/map32.png", 4.f);
}

void Level3::addcolliders()
{
}

void Level3::updatechar(float dt)
{
    player->lastframe = player->pos;
    if (IsKeyDown(KEY_A))
        player->vel.x = -1.0;

    // if (IsKeyDown(KEY_S))
    //     player->vel.y = 1.0;

    if (IsKeyDown(KEY_D))
        player->vel.x = 1.0;

    // if (IsKeyDown(KEY_W))
    //     player->vel.y = -1.0;

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
    player->shouldstay.first ? player->xpos = 896.f : player->xpos = player->pos.x;

    player->ypos = player->pos.y;

    if (player->pos.x > 2816.f)
        player->xpos = player->pos.x - 1920;

    Rectangle source{player->frame * player->width, 0.f, player->right_left * player->width, player->height};
    Rectangle dest{player->xpos, player->ypos, player->scale * player->width, player->scale * player->height};
    DrawTexturePro(player->texture.getTexture(), source, dest, Vector2{}, 0.0, WHITE);
}

void Level3::render()
{
    movecamera = player->shouldstay;
    movecamera.first ? cameramovement.first = 1 : cameramovement.first = 0;
    camx = (player->pos.x - 896.f) * cameramovement.first;

    if (!movecamera.first and (player->pos.x > 1000.f))
    {
        camx = 1920.f;
    }
    
    map1->drawmap(Vector2{camx, camy});
}

void Level3::update(float dt)
{
    updatechar(dt);
}

bool Level3::complete()
{
    return false;
}

void Level3::loadinstr()
{
    instpage.load("assets/pages/instr3.png");
}

void Level3::instr()
{
    DrawTexture(instpage.getTexture(), 0, 0, WHITE);
}