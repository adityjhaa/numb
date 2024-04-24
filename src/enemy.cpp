#include "include/enemy.hpp"

Enemy::Enemy()
{
    texture = idle;
}

Enemy::Enemy(const char *path1, const char *path2, const char *path3)
{
    idle.load(path1);
    run.load(path2);
    hit.load(path3);
    texture = idle;

    width = static_cast<float>(texture.getTexture().width / 11.f);
    height = static_cast<float>(texture.getTexture().height);
}

Enemy::~Enemy()
{
    idle.unload();
    run.unload();
    hit.unload();
}

void Enemy::initenemy(Vector2 pos, int start, int end)
{
    this->pos = pos;
    this->start = start;
    this->end = end;
    frame = 0;
    updateTime = 1.f / 15.f;
    runningTime = 0.f;
}

bool Enemy::followplayer(Vector2 playerpos)
{
    return ((playerpos.x > start) and (playerpos.x < end));
}
