#include "../include/character.hpp"

Character::Character() { texture = idle; }

Character::Character(const char *path1, const char *path2)
{
    idle.load(path1);
    run.load(path2);
    texture = idle;

    width = static_cast<float>(texture.getTexture().width / 11.f);
    height = static_cast<float>(texture.getTexture().height);
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

