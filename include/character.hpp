#pragma once

#include <raylib.h>
#include <raymath.h>
#include "texture.hpp"

class Character
{
    Textures idle, run;
    Textures texture;
    Rectangle rec;
    Vector2 pos, vel;
    int frame, maxframes{11};
    float speed{6.f}, scale{4.f};
    float right_left{1.f}; // right : 1.0, left : -1.0
    float updateTime, runningTime;
    float width, height;

public:
    Character();
    Character(const char *path1, const char *path2);
    ~Character();

    void initchar(Vector2 pos, int frame, float updateTime, float runningTime);
    Vector2 getpos();
    void updatechar(float dt);
};
