#pragma once

#include <raylib.h>
#include <raymath.h>
#include "texture.hpp"

class Character
{
    Textures idle, run;
    Textures texture;
    Rectangle rec;
    Vector2 pos, vel, lastframe;
    float xpos{}, ypos{};
    int frame, maxframes{11};
    std::pair<bool, bool> shouldstay{};
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
    Rectangle getrec();
    void undomove();
    std::pair<bool, bool> movecamera();
    void updatechar(float dt, int level);
};
