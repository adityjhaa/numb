#include "include/character.hpp"

Character::Character() { texture = idle; }

Character::~Character()
{
    idle.unload();
    run.unload();
    jump.unload();
    fall.unload();
    doubleJump.unload();
    hit.unload();
}

Character::Character(const char *path1, const char *path2, const char *path3, const char *path4, const char *path5, const char *path6)
{
    idle.load(path1);
    run.load(path2);
    jump.load(path3);
    fall.load(path4);
    doubleJump.load(path5);
    hit.load(path6);
    texture = idle;

    width = static_cast<float>(texture.getTexture().width / 11.f);
    height = static_cast<float>(texture.getTexture().height);
}

void Character::initchar(Vector2 pos, int frame, float updateTime, float runningTime)
{
    this->pos = pos;
    this->frame = frame;
    this->updateTime = updateTime;
    this->runningTime = runningTime;
}
