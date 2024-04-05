#include "../include/character.hpp"

Character::Character() {}

Character::~Character() {}

void Character::loadTexture(const char *path)
{
    tex = LoadTexture(path);
}

void Character::make(Vector2 pos, int frame, int noframes, float updateTime, float runningTime)
{
    this->noframes = noframes;
    this->frame = frame;
    this->updateTime = updateTime;
    this->runningTime = runningTime;
    rec = Rectangle{0.0, 0.0, (float)tex.width / noframes, (float)tex.height};
    this->pos = pos;
}
