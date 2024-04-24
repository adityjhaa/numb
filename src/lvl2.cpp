#include "include/lvl2.hpp"

void Level2::loadplayer()
{
    player = new Character("assets/main_char/Idle.png", "assets/main_char/Run.png", "assets/main_char/Jump.png", "assets/main_char/Fall.png", "assets/main_char/Double_Jump.png");
    player->initchar(Vector2{256.f, 256.f}, 0, 1.0 / 15.0, 0.f);
}

Level2::Level2()
{
    loadinstr();
    loadplayer();
    loadmap();
    floor = Floor((char *)"assets/maps/floor/Goodfloor.png");
    drops = Droppable();
    multiplier = 1;
    tick = 0;
    score = 0;
    dropsFrequency = 120;
}

Level2::~Level2()
{
    delete player;
    delete map;
    player = nullptr;
    map = nullptr;
}

void Level2::loadmap()
{
    map = new Map("assets/maps/map2.png", 4.f);
}

void Level2::updatechar(float dt)
{
    tick += 1;
    player->lastframe = player->pos;
    if (IsKeyDown(KEY_A))
        player->vel.x = -1.0;
    if (IsKeyDown(KEY_D))
        player->vel.x = 1.0;
    if (IsKeyReleased(KEY_A) || IsKeyReleased(KEY_D))
    {
        player->vel = {};
    }

    if (!floor.CheckCollision(player, player->xpos, player->ypos))
    {
        player->vel.y += .05;
    }
    else
    {
        player->vel.y = 0;
        isIdle = true;
        jumpCount = 0;
    }

    if (IsKeyPressed(KEY_SPACE) && jumpCount < MAX_JUMP_COUNT)
    {
        player->vel.y = -1.f;
        jumpCount += 1;
    }

    if (Vector2Length(player->vel) != 0.0)
    {
        player->pos = Vector2Add(player->pos, Vector2Scale(Vector2Normalize(player->vel), player->speed));

        if (player->vel.x < 0.f)
            player->right_left = -1.f;
        else if (player->vel.x > 0.f)
            player->right_left = 1.f;
    }
    else
    {
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

    // camera
    std::pair<bool, bool> movecamera = player->shouldstay;
    movecamera.first ? cameramovement.first = 1 : cameramovement.first = 0;
    movecamera.second ? cameramovement.second = 1 : cameramovement.second = 0;

    camx = (player->pos.x - 896.f) * cameramovement.first;
    camy = (player->pos.y - 476.f) * cameramovement.second;

    // player textures
    if (player->vel.y > 0)
    {
        player->texture = player->fall;
    }
    if (player->vel.y < 0)
    {
        if (jumpCount == 1)
            player->texture = player->jump;
        else if (jumpCount == 2)
            player->texture = player->doubleJump;
    }
    if (player->vel.y == 0)
    {
        if (player->vel.x == 0)
        {
            player->texture = player->idle;
        }
        else
        {
            player->texture = player->run;
        }
    }

    Rectangle source{player->frame * player->width, 0.f, player->right_left * player->width, player->height};
    Rectangle dest{player->xpos, player->ypos, player->scale * player->width, player->scale * player->height};

    // Difficulty
    if (player->pos.y > 1000)
    {
        multiplier = 5;
    }
    if (player->pos.y > 2000)
    {
        multiplier = 10;
    }

    if (tick % (dropsFrequency) == 0)
    {
        drops.Spaw(player, MAX_DROPS * multiplier);
    }
    if (tick % 60 == 0)
    {
        score += 1;
    }

    floor.Draw(player, camx, camy);
    drops.Draw(GetRandomValue(0, 3), camx, camy);
    drops.CheckCollisions(&floor);
    drops.Update();
    DrawText(("SCORE: " + std::to_string(score)).c_str(), 1336, 128, 96, WHITE);
    DrawTexturePro(player->texture.getTexture(), source, dest, Vector2{}, 0.0, WHITE);
}

unsigned long long int Level2::getScore()
{
    return score;
}

bool Level2::complete()
{
    return (player->pos.y > 2560.f);
}

void Level2::loadinstr()
{
    instpage.load("assets/pages/instr2.png");
}

void Level2::instr()
{
    DrawTexture(instpage.getTexture(), 0, 0, WHITE);
}