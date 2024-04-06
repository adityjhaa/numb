#include "../include/character.hpp"

Character::Character()
{
    texture = idle;
}

Character::Character(const char *path1, const char *path2)
{
    idle.load(path1);
    run.load(path2);
    texture = idle;
}

Character::~Character()
{
    idle.unload();
    run.unload();
}

void Character::initchar(Vector2 pos, int frame, float updateTime, float runningTime)
{
    this->pos = pos;
    this->frame = frame;
    this->updateTime = updateTime;
    this->runningTime = runningTime;
}

void Character::updatechar(float dt)
{
    if (IsKeyDown(KEY_A) or IsKeyDown(KEY_LEFT))
    {
        vel.x -= 1.0;
    }
    if (IsKeyDown(KEY_S) or IsKeyDown(KEY_DOWN))
    {
        vel.y += 1.0;
    }
    if (IsKeyDown(KEY_D) or IsKeyDown(KEY_RIGHT))
    {
        vel.x += 1.0;
    }
    if (IsKeyDown(KEY_W) or IsKeyDown(KEY_UP))
    {
        vel.y -= 1.0;
    }

    if (Vector2Length(vel) != 0.0)
    {
        pos = Vector2Add(pos, Vector2Scale(Vector2Normalize(vel), speed));

        vel.x < 0.f ? right_left = -1.f : right_left = 1.f;

        texture = run;
        maxframes = 12;
    }
    else
    {
        texture = idle;
        maxframes = 11;
    }
    vel = {};

    runningTime += dt;
    if (runningTime >= updateTime)
    {
        runningTime = 0.f;
        frame++;
        frame = frame % maxframes;
    }

    Rectangle source{(float)(frame * texture.getTexture().width)/maxframes, 0.f, (float)(right_left * texture.getTexture().width)/maxframes, (float)texture.getTexture().height};
    Rectangle dest{pos.x, pos.y, (float)(scale * texture.getTexture().width)/maxframes, (float)(scale * texture.getTexture().height)};
    DrawTexturePro(texture.getTexture(), source, dest, Vector2{}, 0.0, WHITE);
}
